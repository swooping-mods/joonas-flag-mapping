#define FEATURE 14
#define MOD_ID "joonas-flag-mapping"
#define HUD_Y 140
#include "runtime.h"
static MoonMapGlobeMarker marks[1024];static DRoot globe_owner;static float globe_radius;
static void feature_end(void){for(int i=0;i<1024;i++)moon_map_globe_marker_remove(marks+i);ddrop(&globe_owner);globe_radius=0;}
static void marker(PTR parent,int index,DVec direction,float radius){
 const float amber[]={1,.57f,.10f,1};
 (void)moon_map_globe_marker_place(marks+index,parent,(MoonMapPoint){direction.x,direction.y,direction.z},radius,1.012f,.015f,amber);
}
static void feature_tick(PTR walker,PTR world,int input){
 (void)walker;int ok=1,count=integer(m.mapping.count,world,&ok);if(!ok||count<0||count>1024){feature_end();show("",0);return;}
 if(host()&&!m.authority_lost&&m.ready&&!m.invalid_store&&m.time>=m.next_scan){m.next_scan=m.time+1;float r=radius(world);DRoot rigs=dhold(objects("MoonJoonasRig",&ok));U64 n=rigs?da.array_length(dget(rigs)):0;if(n>64)n=64;
  for(U64 k=0;k<n;k++){int rig_ok=1;PTR rig=*(PTR*)darray(dget(rigs),k);if(!malive(rig))continue;PTR robot=call(method("MoonCleaners","MoonJoonasRig","get_Robot",0),rig,0,&rig_ok);if(!rig_ok||!malive(robot))continue;PTR rw=0;PTR wf=get_field(object_class(robot),"world");if(wf)field_value(robot,wf,&rw);if(rw!=world)continue;DVec p=mpos(robot,&rig_ok);
   MoonMapWorld source={&m.mapping,world};MoonMapQuery query=moon_map_query(&source);
   int found=rig_ok?moon_map_discover_near(&query,(MoonMapPoint){p.x,p.y,p.z},r,144,m.known,sizeof(m.known)):0;
   if(found){m.dirty=1;for(int i=0;i<found;i++)mevent("robot-discovered-flag");}
  }ddrop(&rigs);
 }
 PTR screen=map();if(!mapopen(screen)){feature_end();show("",0);return;}PTR globe=0;float r=0;PTR gf=get_field(object_class(screen),"globe"),radius_f=get_field(object_class(screen),"globeRadius");if(gf)field_value(screen,gf,&globe);if(radius_f)field_value(screen,radius_f,&r);
 if(!malive(globe)||!(r>0&&r<1e7f)){feature_end();show("",0);return;}
 if(globe!=dget(globe_owner)||r!=globe_radius){feature_end();globe_owner=dhold(globe);if(!globe_owner){show("",0);return;}globe_radius=r;}
 /* Globe is a GameObject in the pinned screen; keep marks in its local frame so
  * vanilla rotation, zoom and occlusion also apply to discoveries. */
 const char *(*class_name)(PTR)=(const char *(*)(PTR))GetProcAddress(GetModuleHandleA("GameAssembly.dll"),"il2cpp_class_get_name");
 const char *kind=class_name?class_name(object_class(globe)):"";PTR parent=deq(kind,"Transform")?globe:call(m.go_tr,globe,0,&ok);if(!ok||!parent){feature_end();show("",0);return;}
 int found=0;for(int i=0;i<1024;i++){
  if(i>=count||!known(i)){moon_map_globe_marker_remove(marks+i);continue;}
  int direction_ok=1;DVec point=direction(world,i,&direction_ok);
  if(!direction_ok){moon_map_globe_marker_remove(marks+i);continue;}found++;marker(parent,i,point,r);
 }
 char text[160],*p=cat(text,"J.O.O.N.A.S. discoveries\n");p=num(p,(U64)found);cat(p," flags mapped / amber globe dots");show(text,input&&found>0);
}
