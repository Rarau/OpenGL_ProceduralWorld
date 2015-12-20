import bpy

cubeMesh = bpy.data.meshes['Cube']

def export_data(filepath):
    out = open(filepath, 'w')
    for poly in cubeMesh.polygons: 
        for idx in (list(poly.vertices)):
            vert = cubeMesh.vertices[idx]
            out.write('{{%f, %f, %f },' % (vert.co.x, vert.co.y, vert.co.z) )
            out.write('{%f, %f, %f }},\n' % (poly.normal[0], poly.normal[1], poly.normal[2]) )
            #out.write(poly.normal)

export_data('C:/cube.txt')
