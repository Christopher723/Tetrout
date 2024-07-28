
#include "block.h"
#include "../core/config.h"
#include "../core/global.h"



shape blocks[7] = {{{255,165,0},
{{0,0,1,0} // L BLOCK
,{1,1,1,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,3}
,{{255,0,0}, // Z BLOCK
{{1,1,0,0}
,{0,1,1,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,3}
,{{224,255,255}, // I BLOCK
{{1,1,1,1}
,{0,0,0,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,4}
,{{0,0,255}, // J BLOCK
{{1,0,0,0}
,{1,1,1,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,3}
,{{255,255,0}, // O BLOCK
{{1,1,0,0}
,{1,1,0,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,2}
,{{0,0,255}, // S BLOCK
{{0,1,1,0}
,{1,1,0,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,3}
,{{128,0,128}, // T BLOCK
{{0,1,0,0}
,{1,1,1,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,3}}, cur;

shape reverseCols(shape s) {
    shape tmp = s;
    for(int i=0; i<s.size; i++) {
        for(int j=0; j<s.size/2; j++) {
            bool t = s.matrix[i][j];
            tmp.matrix[i][j]=s.matrix[i][s.size-j-1];
            tmp.matrix[i][s.size-j-1]=t;
        }
    }
    return tmp;
}
shape transpose(shape s) {
    shape tmp = s;
    for(int i=0; i<s.size; i++) {
        for(int j=0; j<s.size; j++) {
            tmp.matrix[i][j]=s.matrix[j][i];
        }
    }
    return tmp;
}
void rotate() {
    cur =reverseCols(transpose(cur));
}

void draw(shape s, SDL_Rect myRect) {
    for(int i=0; i<s.size; i++) {
        for(int j=0; j<s.size; j++) {
            if(s.matrix[i][j]) {
                myRect.x=(s.x+i)*TILE_SIZE; myRect.y=(s.y+j)*TILE_SIZE;
                SDL_SetRenderDrawColor(gRenderer, s.color.r, s.color.g, s.color.b, 255);
                SDL_RenderFillRect(gRenderer, &myRect);
                SDL_SetRenderDrawColor(gRenderer, 219, 219, 219, 255);
                SDL_RenderDrawRect(gRenderer, &myRect);
            }
        }
    }
}