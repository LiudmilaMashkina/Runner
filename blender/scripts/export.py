import bpy
import json
import os
import sys
sys.path.append('scripts')
import utils


#def get_children_name(obj):
 #       for child in obj.children:
  #          filePath = child.data.uv_textures[0].data[0].image.filepath


print()
print("Export script is running:")
print("CWD: " + os.getcwd())

def get_wall(obj):
    children = []
    mins = []
    maxs = []
    for child in obj.children:
        location = {
            "x": child.location.x,
            "y": child.location.y
        }
        texture_path = utils.get_texture(child)
        indices = utils.get_indices(child)
        vertices = utils.get_vertices(child, indices)

        left_edge = min(vertices, key=lambda v: v["pos"]["x"])["pos"]["x"]
        bottom_edge = min(vertices, key=lambda v: v["pos"]["y"])["pos"]["y"]
        right_edge = max(vertices, key=lambda v: v["pos"]["x"])["pos"]["x"]
        top_edge = max(vertices, key=lambda v: v["pos"]["y"])["pos"]["y"]

        mins.append(child.location.y + bottom_edge)
        maxs.append(child.location.y + top_edge)

        bulbs = []
        for bulb in child.children:
            bulb_location = {
                "x": bulb.location.x,
                "y": bulb.location.y
            }
            bulbs_ref = {
                "type": bulb['type'],
                "location": bulb_location
            }
            bulbs.append(bulbs_ref)

        child_ref = {
            "type": child['type'],
            "location": location,
            "texture_path": texture_path,
            "indices": indices,
            "vertices": vertices,
            "bulbs": bulbs
        }
        children.append(child_ref)
    
    total_bottom = min(mins)
    total_top = max(maxs)
    total_height = total_top - total_bottom

    obj_ref = {
        "children": children,
        "total_height": total_height,
    }
    return obj_ref

    
def get_column(obj):
    texture_path = utils.get_texture(obj)
    indices = utils.get_indices(obj)
    vertices = utils.get_vertices(obj, indices)

    left_edge = min(vertices, key=lambda v: v["pos"]["x"])["pos"]["x"]
    bottom_edge = min(vertices, key=lambda v: v["pos"]["y"])["pos"]["y"]
    right_edge = max(vertices, key=lambda v: v["pos"]["x"])["pos"]["x"]
    top_edge = max(vertices, key=lambda v: v["pos"]["y"])["pos"]["y"]

    original_size = {
        "x": right_edge - left_edge,
        "y": top_edge - bottom_edge
    }
    
    for v in vertices:
        v["pos"]["x"] -= left_edge
        v["pos"]["y"] -= bottom_edge
        print(v["pos"]["x"], v["pos"]["y"])

    children = []
    for child in obj.children:
        location = {
            "x": child.location.x - left_edge,
            "y": child.location.y - bottom_edge
        }
        child_ref = {
            "type": child['type'],
            "location": location
        }
        children.append(child_ref)

    obj_ref = {
        "type": obj['type'],
        "original_size": original_size,
        "vertices": vertices,
        "indices": indices,
        "texture_path": texture_path,
        "children": children
    }
    return obj_ref


root = {}
for obj in bpy.data.objects:
    if obj.parent:
        continue
    if obj['type'] == "column":
        obj_ref = get_column(obj)
        root[obj.name] = obj_ref
    if obj['type'] == "wall-controller":
        obj_ref = get_wall(obj)
        root[obj.name] = obj_ref

json_data = json.dumps(root, sort_keys=True, indent=4, separators=(',', ': '))

filename =  "../resources/objects.json"
with open(filename, 'w') as f:
    f.write(json_data)

print("Export done")
print('\n' * 3)
