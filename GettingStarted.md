

# Using osgwwhich #

**osgwwhich** uses the same search algorithm employed by OSG to find data files and shared libraries, and then displays the full path of the specified file. This is useful when you have multiple data files with the same name, as **osgwwhich** tells you the location of the file that OSG would load. It's also useful when you have multiple copies of OSG installed on your system, as osgwwhich tells you the path to the OSG library or plugin.

For example, the following command shows where OSG will find "cow.osg" (a part of the OpenSceneGraph-Data sample data set):
```
C:\Users\pmartz>osgwwhich cow.osg
C:\Projects\OSG\OSG-Data\cow.osg
```

Note that this works with the OSG notify level. If you wanted to see all the locations that OSG searches before it finds your data file, set the OSG\_NOTIFY\_LEVEL accordingly.
```
C:\Users\pmartz>set OSG_NOTIFY_LEVEL=DEBUG

C:\Users\pmartz>osgwwhich tetra.osg
itr='C:\Projects\OSG\OSG-Data'
FindFileInPath() : trying C:\Projects\OSG\OSG-Data\tetra.osg ...
itr='C:\Projects\Physics\osgBullet\data'
FindFileInPath() : trying C:\Projects\Physics\osgBullet\data\tetra.osg ...
FindFileInPath() : USING C:\Projects\Physics\osgBullet\data\tetra.osg
C:\Projects\Physics\osgBullet\data\tetra.osg
```

The following command locates the OSG OpenFlight plugin:
```
C:\Users\pmartz>osgwwhich osgdb_openflight.dll
C:\Program Files\OpenSceneGraph\bin\osgPlugins-2.8.2\osgdb_openflight.dll
```

The following command displays the osgWorks version number, and also locates the osgUtil library:
```
C:\Users\pmartz>osgwwhich -v osg55-osgUtil.dll
osgWorks version 1.0.0 (10000).

C:\Program Files\OpenSceneGraph\bin\osg55-osgUtil.dll
```

If you don't know the library or plugin name format, use the **-l** and **-p** options with the basic library name or plugin extension. For example, the following command finds the osgUtil library:
```
C:\Users\pmartz>osgwwhich -l osgUtil
C:\Program Files\OpenSceneGraph\bin\osg55-osgUtil.dll
```

And the following command finds the DDS plugin:
```
C:\Users\pmartz>osgwwhich -p dds
Using plugin name: "osgPlugins-2.8.2/osgdb_dds.dll".
C:\Program Files\OpenSceneGraph\bin\osgPlugins-2.8.2\osgdb_dds.dll
```