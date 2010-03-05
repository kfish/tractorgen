#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void *
xmalloc(size_t n)
{
    void *p = malloc(n ? n : 1);
    if (!p)
    {
        perror("malloc");
        exit(1);
    }
    return p;
}


static void
xfree(void *p)
{
    if (p)
        free(p);
}


typedef struct line_t line_t;
struct line_t
{
    size_t ncolumns;
    size_t ncolumns_max;
    unsigned char *text;
    size_t min_x;
    size_t max_x;
};


static void
line_constructor(line_t *lp)
{
    lp->ncolumns = 0;
    lp->ncolumns_max = 0;
    lp->text = 0;
    lp->min_x = 0;
    lp->max_x = 0;
}


static void
line_destructor(line_t *lp)
{
    xfree(lp->text);
}


static void
line_stash(line_t *lp, int sx, int c)
{
    if (sx < 0)
        return;
    if (c == ' ')
        return;
    size_t x = sx;
    while (x >= lp->ncolumns_max)
    {
        size_t new_ncolumns_max = lp->ncolumns_max * 2 + 32;
        unsigned char *new_text = xmalloc(new_ncolumns_max);
        memcpy(new_text, lp->text, lp->ncolumns_max);
        memset(new_text + lp->ncolumns_max, ' ',
            new_ncolumns_max - lp->ncolumns_max);
        xfree(lp->text);
        lp->text = new_text;
        lp->ncolumns_max = new_ncolumns_max;
    }

    if (lp->ncolumns == 0)
    {
        lp->min_x = x;
        lp->max_x = x + 1;
    }
    else
    {
        if (lp->min_x > x)
            lp->min_x = x;
        if (lp->max_x <= x)
            lp->max_x = x + 1;
    }

    if (x >= lp->ncolumns)
        lp->ncolumns = x + 1;
    lp->text[x] = c;
}


static void
line_print(const line_t *lp)
{
    printf("%.*s\n", (int)lp->ncolumns, lp->text);
}


static int
line_get(const line_t *lp, int sx)
{
    if (sx < 0)
        return ' ';
    size_t x = sx;
    if (x >= lp->ncolumns)
        return ' ';
    return lp->text[x];
}


typedef struct picture_t picture_t;
struct picture_t
{
    size_t nlines;
    size_t nlines_max;
    line_t *line;
};


static void
picture_constructor(picture_t *pp)
{
    pp->nlines = 0;
    pp->nlines_max = 0;
    pp->line = 0;
}


static void
picture_destructor(picture_t *pp)
{
    size_t y;
    for (y = 0; y < pp->nlines; ++y)
        line_destructor(&pp->line[y]);
    xfree(pp->line);
}


static void
picture_stash(picture_t *pp, int x, int sy, int c)
{
    if (x < 0 || sy < 0)
        return;
    size_t y = sy;
    if (y >= pp->nlines_max)
    {
        size_t j;
        size_t new_nlines_max = pp->nlines_max * 2 + 8;
        line_t *new_lines = xmalloc(new_nlines_max * sizeof(line_t));
        for (j = 0; j < pp->nlines; ++j)
            new_lines[j] = pp->line[j];
        xfree(pp->line);
        pp->line = new_lines;
        pp->nlines_max = new_nlines_max;
        for (; j < pp->nlines_max; ++j)
            line_constructor(&pp->line[j]);
    }
    if (y >= pp->nlines)
        pp->nlines = y + 1;
    line_stash(&pp->line[y], x, c);
}


static void
picture_print(const picture_t *pp)
{
    size_t y;
    for (y = 0; y < pp->nlines; ++y)
        line_print(&pp->line[y]);
}


static int
picture_get_min_x(const picture_t *pp)
{
    if (!pp->nlines)
        return 0;
    int min_x = pp->line[0].min_x;
    size_t y;
    for (y = 1; y < pp->nlines; ++y)
    {
        if (pp->line[y].ncolumns)
        {
            int x = pp->line[y].min_x;
            if (x < min_x)
                min_x = x;
        }
    }
    return min_x;
}


static int
picture_get_max_x(const picture_t *pp)
{
    if (!pp->nlines)
        return 0;
    int max_x = 0;
    size_t y;
    for (y = 0; y < pp->nlines; ++y)
    {
        int x = pp->line[y].max_x;
        if (x > max_x)
            max_x = x;
    }
    return max_x;
}


static int
picture_get(const picture_t *pp, int x, int sy)
{
    if (sy < 0)
        return ' ';
    size_t y = sy;
    if (y >= pp->nlines)
        return ' ';
    return line_get(&pp->line[y], x);
}


static void
picture_offset(const picture_t *src, int dx, picture_t *dst)
{
    int lox = picture_get_min_x(src);
    int hix = picture_get_max_x(src);
    size_t y;
    for (y = 0; y < src->nlines; ++y)
    {
        int x;
        for (x = lox; x < hix; ++x)
        {
            int c = picture_get(src, x, y);
            int x2 = x + dx;
            if (x2 < 80)
                picture_stash(dst, x + dx, y, c);
        }
    }
}


int
main()
{
    /*
     * read the tractor from stdin.
     */
    picture_t p;
    picture_constructor(&p);
    int x = 0;
    int y = 0;
    for (;;)
    {
        int c = getchar();
        if (c == EOF)
            break;
        if (c == '\n')
        {
            x = 0;
            ++y;
            continue;
        }
        picture_stash(&p, x, y, c);
        ++x;
    }

    int hix = picture_get_max_x(&p);

    int first = 1;
    int dx;
    for (dx = 1 - hix; dx < 80 - hix; ++dx)
    {
        if (!first)
        {
            usleep(50000);
            printf("\33[%dA", (int)p.nlines);
        }
        picture_t p2;
        picture_constructor(&p2);
        picture_offset(&p, dx, &p2);
        picture_print(&p2);
        picture_destructor(&p2);
        fflush(stdout);
        first = 0;
    }
    return 0;
}
