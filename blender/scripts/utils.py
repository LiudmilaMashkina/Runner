import bpy
import json
import os

def get_texture(obj):
    filename = bpy.data.filepath
    img = obj.data.uv_textures[0].data[0].image.filepath
    folder = os.path.dirname(filename)
    img = img.replace('//', '')
    res = os.path.join(folder, img)
    cwd = os.getcwd()
    tmp = os.path.relpath(res, cwd)
    texture_path = tmp.replace(os.path.sep, '/')
    return texture_path

def get_indices(obj):
    indices = []
    for p in obj.data.polygons:
        for index in p.vertices:
            indices.append(index)
    return indices

def get_vertices(obj, indices):
    vertices = [] 
    for vert in obj.data.vertices:
        pos = {
            "x": vert.co[0],
            "y": vert.co[1]
        }
        data = {
            "pos": pos
        }
        vertices.append(data)
    uv_data = obj.data.uv_layers.active.data
    for i in range(0, len(uv_data)):
        tex_co = {
            "u": uv_data[i].uv.x,
            "v": uv_data[i].uv.y
        }
        vertex_index = indices[i]
        data = vertices[vertex_index]
        data["tex_co"] = tex_co

    return vertices



        


