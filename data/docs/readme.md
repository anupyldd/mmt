# Table of contents:
- [Table of contents:](#table-of-contents)
- [Pack Structure](#pack-structure)
- [Pack Rules](#pack-rules)
- [Pack Distribution](#pack-distribution)
- [Brush Scripting](#brush-scripting)
  - [Brushes](#brushes)
  - [Brush parameters](#brush-parameters)
  - [Available API functions](#available-api-functions)

# Pack Structure

A resource pack is a zip archive that contains textures, object images,
fonts, scripts, etc. that can be used when creating a map.

The structure of a pack is as follows:
```
pack (archive):
    
    - metadata.json  (name, author, version, description, update time)
    - license.txt    (pack license)
    - notice.txt     (includes all required license notices for 3rd party assets)
    - readme.txt     (additional information about the pack)

    textures:  
        - texture1.png
        - texture2.png
        - ...

    objects: (e.g., stamps, icons—images that are not textures)
        - object1.png
        - object2.png
        - ...

    fonts:
        - font1.ttf
        - font2.ttf
        - ...
        
    brushes:
        - brush1.lua
        - brush2.lua
        - ...
```
# Pack Rules

- All files within the same category (textures, objects, etc.) must have unique names, regardless of sub-folder placement. For instance, all textures in the textures directory must have unique names, even if they are placed in sub-folders of the category. 

- Supported image formats: `PNG`, `JPG`, `JPEG`, `BMP`, `TGA`.

- Supported font formats: `TTF`, `OTF`.
    
- You may leave out the metadata, readme, license and notice files if you don't plan to distribute the pack or if you do not need them (e.g. there's no need for a readme file, if it's empty).

# Pack Distribution

- Always credit the authors of 3rd party assets, even if they distribute their work under CC0/Public domain.
      
- Do not distribute resources that you have no rights to distribute.
    
- If an asset comes with a license file, include its text in the `notice.txt`.
    
- Resources can be stored as plain files or in .rres archives. Ensure that files are placed in the correct directories for proper interpretation. For example, an object image placed in the `textures` directory will be treated as a texture.

- The date in the metadata file should follow the format `YYYY.MM.DD`.

# Brush Scripting

## Brushes

Brushes are implemented as Lua scripts. This allows you to create your own custom brushes and use them when creating a map.
    
Brush scripts consist of several functions that are called by the program. These have to be present in each script, although they can be empty:
    
- ### OnLoad():
    Called when brush is fist loaded or when it is reloaded at runtime. Here you should load all the needed resources.
                
- ### OnHover():
    This function is called when you are hovering the brush over the canvas. Here you can, for example, set the preview that would be visible before user starts painting.
                    
- ### OnPress():
    This function is called on the frame the brush starts painting (e.g.when user presses the LMB).
                    
- ### OnHold():
    This function is called each frame after the start of painting and until the end of painting. Here's where most of painting takes place. You can adjust the result each frame according to some rules or just use a consistent shape.
                    
- ### OnRelease():  
    This function is called on the frame painting stops (e.g. the LMB is released).
                    
## Brush parameters

TODO: parameters that are visible in the program
                    
## Available API functions
You can use these functions in your brush scripts along with standard Lua library.

*Note: coordinates for both screen and canvas start from the top-left corner; `x` axis goes left to right, `y` axis goes top to bottom.*

- ### GetResource()

    **Returns:**
    
    Reference to the requested resource if found. Not recommended to use in functions that are called often (like `OnHold`).

  **Parameters:**
  - resource type (`"texture"` / `"object"` / `"font"`)
  - pack name (can be `"this"` if the resource is in the same pack)
  - resource name (including extention, e.g. `"tree.png"`)

    
                        
- ### GetMousePosScreen()
  
    **Returns:**
    
    A table with two values (`x` and `y`) that correspond to mouse position on the screen.
 
    **Parameters:**
    - no parameters
                            
- ### GetMousePosCanvas()
  
    **Returns:**
    
    A table with two values (`x` and `y`) that correspond to mouse position on the canvas.
 
    **Parameters:**
    - no parameters

- ### GetColorScreen()
    **Returns:** 
    
    A table with four values (`r`, `g`, `b`, `a`) holding the color of a pixel on screen at a given coordinate.

    **Parameters:**
    - `x` coordinate
    - `y` coordinate

- ### GetColorCanvas()
    **Returns:** 
    
    A table with four values (`r`, `g`, `b`, `a`) holding the color of a pixel on canvas at a given coordinate.

    **Parameters:**
    - `x` coordinate
    - `y` coordinate