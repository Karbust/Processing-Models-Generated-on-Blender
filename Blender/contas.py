import bpy
import time
from mathutils import Vector
from operator import itemgetter

ob = bpy.context.object
me = ob.data

print("Vertices: ", len(me.vertices))
print("Arestas: ", len(me.edges))
print("Faces: ", len(me.polygons)) # faces
