import bpy
import bmesh
from mathutils import Vector

# 3D tri area ABC is half the length of AB cross product AC 
def tri_area( co1, co2, co3 ):
    return (co2 - co1).cross( co3 - co1 ).length / 2.0

# Get the object
obj = bpy.context.object

# Construct bmesh
bm = bmesh.new()
bm.from_mesh( obj.data )

# Triangulate it so that we can calculate tri areas
bmesh.ops.triangulate( bm, faces = bm.faces )

# Ensure faces access
bm.faces.ensure_lookup_table()

area = 0;

# enumerate the faces
for face in bm.faces:
    # Get the face area (can also be 'face.calc_area()')
    face_area = tri_area( *(v.co for v in face.verts) )
    area += face_area
    print( face.index, face_area )
    
print(area)