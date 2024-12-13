A resource pack is a zip archive that contains textures, object images
and fonts that can be used when creating a map.

The general structure of a pack is as follows:

pack (archive):
    
    - metadata.json  (name, author, version, description, update time)
    - license.txt    (pack license)
    - notice.txt     (includes all required license notices for 3rd party assets)
    - readme.txt     (additional information about the pack)

    textures:  
        - texture1.png
        - texture2.png
        - texture_archive.rres
        - ...

    objects: (e.g., stamps, icons—images that are not textures)
        - object1.png
        - object2.png
        - object_archive.rres
        - ...

    fonts:
        - font1.ttf
        - font2.ttf
        - font_archive.rres
        - ...

***********************************************************************************

Notes:

    - Currently, the folder structure inside the textures, objects, and fonts directories 
      is ignored. For example, if you place a file in objects/somedir/object.png, it will 
      still be treated as if it were in the root objects folder. This behavior may change 
      in future updates.

    - All files within the same directory must have unique names, regardless of sub-folder 
      placement. For instance, all textures in the textures directory must have unique names, 
      even if they are placed in sub-folders like textures/subfolder/. However, files in 
      different directories (e.g., textures and objects) can share the same name.

    - Supported image formats: PNG, JPG, JPEG, BMP, TGA.

    - Supported font formats: TTF, OTF.

    - You may leave out the metadata, readme, license and notice files if you don't plan
      to distribute the pack or if you do not need them (e.g. there's no need for a readme
      file, if it's empty).

In case you're planning to distribute the pack:

    - Always credit the authors of 3rd party assets, even if they distribute their
      work under CC0/Public domain.
    
    - If an asset comes with a license file, include its text in the notice.txt.
    
    - Resources can be stored as plain files or in .rres archives. Ensure that
      files are placed in the correct directories for proper interpretation. For example,
      an object image placed in the `textures` directory will be treated as a texture.

    - The date in the metadata file should follow the format "YYYY.MM.DD".
