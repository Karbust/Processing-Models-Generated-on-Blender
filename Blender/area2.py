import bpy
import bmesh

obj = bpy.context.active_object

bm = bmesh.new()
bm.from_mesh(obj.data)

area = sum(f.calc_area() for f in bm.faces)
print(area)

bm.free()