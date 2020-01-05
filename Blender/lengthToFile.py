import bpy
import time

#Calc the length between 2 vertices given by vertex index
def CalcLength( obj, vertices ):
    v1 = obj.data.vertices[vertices[0]] #Get the first
    v2 = obj.data.vertices[vertices[1]] #Get the second
    return (v1.co - v2.co).length #Calculate the length from their coordinates

#In object mode
obj = bpy.context.object #selected object
#obj = bpy.data.objects['name'] #or by name

fileName = "C:\\Users\\Karbust\\Desktop\\example.txt" #Your file name

file = open( fileName, 'w+' ) #Open a file (will create or erase an existing one

startTime = time.time()

try:
    #Write to the file the length of each edge
    file.write( '\n'.join([str(CalcLength(obj, e.vertices)) for e in obj.data.edges] ) )
finally:
    file.close()

executionTime = time.time() - startTime
print( executionTime )