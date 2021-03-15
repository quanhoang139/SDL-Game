#include "Core.h"

void Core::handlingEvent(SDL_Event &e)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    canMove = false;
    if(y < 100 || y > 500 || x < 0 || x > 400) return;
    int i = x / 40, j = (y - 100) / 40;
    if(a[j][i] == -1) return;
    if(j > 0 && a[j - 1][i] == a[j][i]) canMove = true;
    if(i > 0 && a[j][i - 1] == a[j][i]) canMove = true;
    if(j < 9 && a[j + 1][i] == a[j][i]) canMove = true;
    if(i < 9 && a[j][i + 1] == a[j][i]) canMove = true;
}

const int dh[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

void Core::solve()
{
    if(!canMove) return;
    int x, y;
    SDL_GetMouseState(&x, &y);
    int i = x / 40, j = (y - 100) / 40;
    while(!q.empty()) q.pop();
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j) color[i][j] = 0;
    q.push(i * 40 + j);
    color[j][i] = 1;
    while(!q.empty())
    {
        int id = q.front();
        q.pop();
        i = id / 40; j = id % 40;
        for(int k = 0; k < 4; ++k)
        {
            if (j + dh[k] < 0 || j + dh[k] > 9 || i + dc[k] < 0 || i + dc[k] > 9) continue;
            if(color[j + dh[k]][i + dc[k]] == 0 && a[j + dh[k]][i + dc[k]] == a[j][i])
            {
                q.push((i + dc[k]) * 40 + j + dh[k]);
                color[j + dh[k]][i + dc[k]] = 1;
            }
        }
        a[j][i] = -1;
    }
    canMove = false;

    for(int i = 0; i < 10; ++i)
    {
        while(!q.empty()) q.pop();
        for(int j = 9; j >= 0; --j)
        {
            if(a[j][i] != -1) q.push(a[j][i]);
        }
        for(int j = 9; j >= 0; --j)
        {
            if(!q.empty()) a[j][i] = q.front(), q.pop();
            else a[j][i] = -1;
        }
    }

    while(!q.empty()) q.pop();

    for(int i = 0; i < 10; ++i)
    {
        if(a[9][i] != -1) q.push(i);
    }
    for(int i = 0; i < 10; ++i)
    {
        if(!q.empty()) {
            int id = q.front();
            q.pop();
            for(int j = 0; j < 10; ++j) a[j][i] = a[j][id];
        }
        else {
            for(int j = 0; j < 10; ++j) a[j][i] = -1;
        }
    }

}
