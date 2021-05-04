#include "Core.h"

void Core::init(SDL_Renderer* &renderer) {
    gameTexture.loadMedia(renderer);

    freopen("save.txt", "r", stdin);

    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j) cin >> a[i][j];
    cin >> score;
    cin >> level;
    cin >> target;
    cin >> more;
    cin >> scount;
    for (int i = 0; i < 5; ++i) cin >> highscore[i].first >> highscore[i].second;
    if (a[9][0] == -1) continuePre = false;
    else continuePre = true;
    curRun = MENU;
    curHighScore = highscore[0].first;
    gameSound.load();
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    button[0].loadButton(renderer, 256, 50, 200 - 128, 300, "asset/Image/new game.png");
    button[1].loadButton(renderer, 256, 50, 200 - 128, 380, "asset/Image/continue.png", "asset/Image/continue black.png");
    button[2].loadButton(renderer, 256, 50, 200 - 128, 460, "asset/Image/record.png");
    button[3].loadButton(renderer, 85, 40, 72 , 540, "asset/Image/vol on.png", "asset/Image/vol off.png");
    button[4].loadButton(renderer, 85, 40, 243, 540, "asset/Image/mus on.png", "asset/Image/mus off.png");
    button[5].loadButton(renderer, 40, 40, 310, 10, "asset/Image/small vol on.png", "asset/Image/small vol off.png");
    button[6].loadButton(renderer, 40, 40, 360, 10, "asset/Image/small mus on.png", "asset/Image/small mus off.png");
    button[7].loadButton(renderer, 40, 40, 260, 10, "asset/Image/home.png");
    button[8].loadButton(renderer, 220, 50, 90, 458);
    button[9].loadButton(renderer, 40, 40, 10, 60, "asset/Image/back.png");
}

void Core::handlingEvent(SDL_Event &e)
{
    if (curRun == MENU) {
        if (button[0].checkUserClickPos()) {
            for(int i = 0; i < 10; ++i)
            for(int j = 0; j < 10; ++j) a[i][j] = rand() % 5;
            score = 0; level = 1;
            target = 1000; more = 1500;
            scount = 2;
            gameOver = false;
            stageClear = false;
            curRun = INGAME;
            //Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
        }
        else if (button[1].checkUserClickPos()) {
            if (continuePre) {
                gameOver = false;
                stageClear = false;
                curRun = INGAME;
                //Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
            }
        }
        else if (button[2].checkUserClickPos()) {
            curRun = RECORD_LIST;
            //Mix_VolumeMusic(MIX_MAX_VOLUME);
        }
        else if (button[3].checkUserClickPos()) gameSound.changeEffectVol();
        else if (button[4].checkUserClickPos()) gameSound.changeMusicVol();
    }
    else if (curRun == INGAME) {
        if (!erasedBlockID.empty()) return;
        if (button[5].checkUserClickPos()) gameSound.changeEffectVol();
        else if (button[6].checkUserClickPos()) gameSound.changeMusicVol();
        else if (button[7].checkUserClickPos()) {
            continuePre = true;
            curRun = MENU;
            //Mix_VolumeMusic(MIX_MAX_VOLUME);
        }
        else {
            int x, y;
            SDL_GetMouseState(&x, &y);
            canMove = false;
            if(y < 200 || y > 600 || x < 0 || x > 400) return;
            int i = x / 40, j = (y - 200) / 40;
            if(a[j][i] == -1) return;
            if(j > 0 && a[j - 1][i] == a[j][i]) canMove = true;
            if(i > 0 && a[j][i - 1] == a[j][i]) canMove = true;
            if(j < 9 && a[j + 1][i] == a[j][i]) canMove = true;
            if(i < 9 && a[j][i + 1] == a[j][i]) canMove = true;
            if (canMove) gameSound.playEffect(Sound::CLICK_CAT);
        }
    }
    else if (curRun == NXLVBOARD) {
        if (button[8].checkUserClickPos()) curRun = INGAME;//, Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    }
    else {
        if (button[9].checkUserClickPos()) curRun = MENU;//, Mix_VolumeMusic(MIX_MAX_VOLUME);
    }
}

const int dh[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

void Core::solve()
{
    if(!canMove) return;
    int x, y;
    SDL_GetMouseState(&x, &y);
    int i = x / 40, j = (y - 200) / 40;
    while(!q.empty()) q.pop();
    while(!erasedBlockID.empty()) erasedBlockID.pop();
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j) color[i][j] = 0;
    q.push(i * 40 + j);
    color[j][i] = 1;
    while(!q.empty())
    {
        int id = q.front();
        erasedBlockID.push(id);
        q.pop();
        i = id / 40; j = id % 40;
        catColor = a[j][i];
        for(int k = 0; k < 4; ++k)
        {
            if (j + dh[k] < 0 || j + dh[k] > 9 || i + dc[k] < 0 || i + dc[k] > 9) continue;
            if(color[j + dh[k]][i + dc[k]] == 0 && a[j + dh[k]][i + dc[k]] == a[j][i])
            {
                q.push((i + dc[k]) * 40 + j + dh[k]);
                color[j + dh[k]][i + dc[k]] = 1;
            }
        }
        //a[j][i] = -1;
    }
    score += 5 * int(erasedBlockID.size() * erasedBlockID.size());
    if (score > curHighScore) curHighScore = score;
    canMove = false;
}

void Core :: solveTexture(SDL_Renderer* renderer)
{
    if (id != erasedBlockID.front()) {
        for (int i = 0; i < TOTAL_PARTICAL; ++i) {
            partical[i] = new Partical(erasedBlockID.front());
        }
        cnt++;
        if (cnt > 14) cnt = 1;
        gameSound.playEffect(cnt);
        id = erasedBlockID.front();
        a[id % 40][id / 40] = -1;
    }
    bool ok = false;
    for (int i = 0; i < TOTAL_PARTICAL; ++i) if (!partical[i]->isDead()) ok = true;
    if (ok) {
        for (int i = 0; i < TOTAL_PARTICAL; ++i) if(!partical[i]->isDead())
            partical[i]->render(renderer, gameTexture.getCatTexture(catColor));
    }
    else {
        erasedBlockID.pop();
        for (int i = 0; i < TOTAL_PARTICAL; ++i) delete partical[i];
    }
}

void Core::newLevel() {
    int cnt = 0;
    for(int i = 9; i >= 0; --i)
        for(int j = 9; j >= 0; --j)
        if(a[j][i] != -1) cnt++;
    if(cnt < 10) {
        score += (10 - cnt) * 100;
        if (score > curHighScore) curHighScore = score;
    }
    ++level;
    target += more;
    scount--;
    if(scount == 0) more += 500, scount = 2;
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j) a[i][j] = rand() % 5;

    canMove = false;
}

void Core::saveData() {
    freopen("save.txt", "w", stdout);
    if (!continuePre) {
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j) a[i][j] = -1;
        score = 0;
        level = 1;
        target = 1000;
        more = 1500;
        scount = 2;
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) cout << a[i][j] << " ";
        cout << endl;
    }
    cout << score << endl;
    cout << level << endl;
    cout << target << endl;
    cout << more << endl;
    cout << scount << endl;
    for (int i = 0; i < 5; ++i)
        cout << highscore[i].first << " " << highscore[i].second << endl;
}

void Core::renderTexture(SDL_Renderer* renderer) {
    switch(curRun) {
        case MENU: renderMenu(renderer); break;
        case INGAME: renderInGame(renderer); break;
        case NXLVBOARD: renderNXLVBoard(renderer); break;
        case RECORD_LIST: renderRecordList(renderer); break;
    }
}

void Core::renderMenu(SDL_Renderer* renderer) {
    gameTexture.renderMenu(renderer);
    if (continuePre) button[1].reloadButton(0);
    else button[1].reloadButton(1);

    if (gameSound.getEffectVol())
        button[3].reloadButton(0);
    else button[3].reloadButton(1);

    if (gameSound.getMusicVol())
        button[4].reloadButton(0);
    else button[4].reloadButton(1);

    for (int i = 0 ; i < 5; ++i)
        button[i].renderButton(renderer);
}

void Core::renderInGame(SDL_Renderer* renderer) {
    if (gameOver) {
        if (Mix_Playing(2)) gameTexture.renderGameOver(renderer, score, level, target, curHighScore);
        else {
            gameOver = false;
            curRun = MENU;
        }
        return;
    }
    if (stageClear) {
        if (Mix_Playing(2)) gameTexture.renderStageClear(renderer, a, score, level, target, curHighScore);
        else {
            stageClear = false;
            newLevel();
            curRun = NXLVBOARD;
        }
        return;
    }
    gameTexture.renderMedia(renderer, a, score, level, target, curHighScore);
    //gameTexture.renderNXLVBoard(renderer, score, level, target);

    if (gameSound.getEffectVol())
        button[5].reloadButton(0);
    else button[5].reloadButton(1);

    if (gameSound.getMusicVol())
        button[6].reloadButton(0);
    else button[6].reloadButton(1);

    for (int i = 5; i < 8; ++i)
        button[i].renderButton(renderer);
    if(!erasedBlockID.empty())
    {
        solveTexture(renderer);
    }
    else {
        id = -1; cnt = 0;
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
        bool pass = true;
        for(int i = 0; i < 10; ++i) {
            if(a[9][i] != -1)
            {
                for(int j = 0; j < 10; ++j) if (a[j][i] != -1) {
                    for(int k = 0; k < 4; ++k)
                    {
                        if (j + dh[k] < 0 || j + dh[k] > 9 || i + dc[k] < 0 || i + dc[k] > 9) continue;
                        if(a[j + dh[k]][i + dc[k]] == a[j][i]) {
                            pass = false; break;
                        }
                    }
                }
            }
        }
        if (pass) {
            if (score >= target) {
                gameSound.playEffect(Sound::STAGE_CLEAR);
                stageClear = true;
                gameOver = false;
                continuePre = false;
                return;
            }
            else {
                for (int i = 0; i < 5; ++i) {
                    if (highscore[i].first < score) {
                        for (int j = 4; j > i; --j) highscore[j] = highscore[j - 1];
                        highscore[i] = std::pair<int, int> (score, level);
                        break;
                    }
                }
                gameSound.playEffect(Sound::GAME_OVER);
                gameOver = true;
                stageClear = false;
                continuePre = false;
                return;
            }
        }
    }
}

void Core::renderNXLVBoard(SDL_Renderer* renderer) {
    gameTexture.renderNXLVBoard(renderer, score, level, target);
}

void Core::renderRecordList(SDL_Renderer* renderer) {
    gameTexture.renderRecordList(renderer, highscore);
    button[9].renderButton(renderer);
}
