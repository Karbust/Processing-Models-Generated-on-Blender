import bpy 
import bmesh 

ob = bpy.context.active_object 
me = ob.data 
bm = bmesh.new() 
bm.from_mesh(me)
bm.normal_update()

print('bmesh:', bm) 

for f in bm.faces: 
    print('face index:', f.index ,' and face normal:', f.normal)