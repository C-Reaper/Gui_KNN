#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"
#include "/home/codeleaded/System/Static/Library/KNN.h"

#define KNN_CENTER_PATH     "./data/Output." KNN_CENTER_FILETYPE
#define KNN_DATA_PATH       "./data/Output." KNN_DATA_FILETYPE
#define KNN_LEARNRATE       0.5f
#define KNN_RADIUS          0.01f
#define KNN_STARTPOINTS     50

TransformedView tv;
KNN knn;

void Setup(AlxWindow* w){
    RGA_Set(Time_Nano());

	tv = TransformedView_New((Vec2){ GetWidth(),GetHeight() });
	knn = KNN_New(3U,2U,3U);
}
void Update(AlxWindow* w){
    tv.ZoomSpeed = 1.0f * w->ElapsedTime;
	TransformedView_HandlePanZoom(&tv,window.Strokes,GetMouse());
    Vec2 const mp = TransformedView_ScreenWorldPos(&tv,GetMouse());

    if(Stroke(ALX_KEY_1).PRESSED){
        KNN_Add_Data(&knn,(KNN_DataPoint[]){
            KNN_DataPoint_Make((NeuralType[]){ mp.x,mp.y },2,0),
            KNN_DataPoint_Null()
        });
    }else if(Stroke(ALX_KEY_2).PRESSED){
        KNN_Add_Data(&knn,(KNN_DataPoint[]){
            KNN_DataPoint_Make((NeuralType[]){ mp.x,mp.y },2,1),
            KNN_DataPoint_Null()
        });
    }else if(Stroke(ALX_KEY_3).PRESSED){
        KNN_Add_Data(&knn,(KNN_DataPoint[]){
            KNN_DataPoint_Make((NeuralType[]){ mp.x,mp.y },2,2),
            KNN_DataPoint_Null()
        });
    }
    
    if(Stroke(ALX_MOUSE_L).PRESSED){
        NeuralType mdata[] = { mp.x,mp.y };
        const int out = KNN_Centerize(&knn,mdata);

        KNN_Add_Data(&knn,(KNN_DataPoint[]){
            KNN_DataPoint_Make(mdata,2,out),
            KNN_DataPoint_Null()
        });
    }
    if(Stroke(ALX_MOUSE_R).PRESSED){
        for(int i = 0;i<knn.dps.size;i++){
            KNN_DataPoint* nt = (KNN_DataPoint*)Vector_Get(&knn.dps,i);
            const Vec2 d = Vec2_Sub(mp,(Vec2){ nt->data[0],nt->data[1] });
            const float d2 = Vec2_Mag2(d);
            
            if(d2 < KNN_RADIUS * KNN_RADIUS){
                KNN_DataPoint_Free(nt);
                Vector_Remove(&knn.dps,i);
                break;
            }
        }
    }

	Clear(BLACK);

	Vec2 const sp = TransformedView_WorldScreenPos(&tv,(Vec2){ 0.0f,0.0f });
	Vec2 const sd = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });
	Rect_RenderXWire(WINDOW_STD_ARGS,sp,sd,WHITE,1.0f);

	Vec2 const ntd = TransformedView_WorldScreenLength(&tv,(Vec2){ KNN_RADIUS,KNN_RADIUS });
    for(int i = 0;i<knn.dps.size;i++){
        KNN_DataPoint* dp = (KNN_DataPoint*)Vector_Get(&knn.dps,i);
        
        Pixel color = WHITE;
        if(dp->i_out == 0)      color = RED;
        else if(dp->i_out == 1) color = GREEN;
        else if(dp->i_out == 2) color = YELLOW;
        
        Vec2 const ntp = TransformedView_WorldScreenPos(&tv,(Vec2){ dp->data[0],dp->data[1] });
        Circle_R_Render(WINDOW_STD_ARGS,ntp,ntd,color);
    }
}
void Delete(AlxWindow* w){
    KNN_Free(&knn);
}

int main(){
    if(Create("KNN",1900,1100,1,1,Setup,Update,Delete))
        Start();
    return 0;
}