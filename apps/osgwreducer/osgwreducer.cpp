/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * osgWorks is (C) Copyright 2009-2013 by Kenneth Mark Bryden
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#include <osgwTools/GeometryModifier.h>
#include <osgwTools/ReducerOp.h>
#include <osgUtil/Optimizer>

#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osg/Notify>


int main( int argc, char** argv )
{
    osg::ArgumentParser arguments(&argc, argv);

    arguments.getApplicationUsage()->setApplicationName(arguments.getApplicationName());
    arguments.getApplicationUsage()->setDescription(arguments.getApplicationName() + "  runs the Reducer GeometryOperation on the specified input model, and writes the processed model to disk.");
    arguments.getApplicationUsage()->setCommandLineUsage(arguments.getApplicationName() + " [options] <inputfile> <outputfile>");

    arguments.getApplicationUsage()->addCommandLineOption("--no-remove-degenerate", "Do not remove degenerate/redundant triangles");
    arguments.getApplicationUsage()->addCommandLineOption("--group-threshold", "Specify threshold for groups.");
    arguments.getApplicationUsage()->addCommandLineOption("--max-edge-error", "Maximum edge error");

    if (arguments.read("-h") || arguments.read("--help"))
    {
        osg::notify(osg::ALWAYS) << arguments.getApplicationUsage()->getDescription() << std::endl;
        arguments.getApplicationUsage()->write(osg::notify(osg::ALWAYS), osg::ApplicationUsage::COMMAND_LINE_OPTION);
        return 1;
    }

    bool removeDegenerate(true);
    float groupThreshold = 10.0f;
    float maxEdgeError = 10.0f;
    if (arguments.find("--no-remove-degenerate") > 0)
        removeDegenerate = false;
    std::string str;
    while (arguments.read("--group-threshold", str))
    {
        float nsimp = 1.0;
        if (sscanf(str.c_str(), "%f",
            &nsimp) != 1)
        {
            std::cerr << arguments.getApplicationName() << ": group-threshold format incorrect (" << str << ")." << std::endl;
            return 1;
        }
    }
    while (arguments.read("--max-edge-error", str))
    {
        float nsimp = 1.0;
        if (sscanf(str.c_str(), "%f",
            &nsimp) != 1)
        {
            std::cerr << arguments.getApplicationName() << ": max-edge-error format incorrect (" << str << ")." << std::endl;
            return 1;
        }
    }

    // any option left unread are converted into errors to write out later.
    arguments.reportRemainingOptionsAsUnrecognized();

    // report any errors if they have occurred when parsing the program arguments.
    if (arguments.errors())
    {
        arguments.writeErrorMessages(std::cout);
        return 1;
    }
    std::vector<std::string> fileNames;
    for (int pos = 1; pos < arguments.argc(); ++pos)
    {
        if (!arguments.isOption(pos))
        {
            fileNames.push_back(arguments[pos]);
        }
    }

    std::string fileNameOut("converted.osg");
    if (fileNames.size() > 1)
    {
        fileNameOut = fileNames.back();
        fileNames.pop_back();
    }


    osg::ref_ptr<osg::Node> model = osgDB::readRefNodeFiles(fileNames);
    if( !model.valid() )
    {
        OSG_FATAL << "Can't read input file \"" << fileNames.front() << "\"" << std::endl;
        return( 1 );
    }

    osg::ref_ptr<osgwTools::ReducerOp> op = new osgwTools::ReducerOp;
    op->setGroupThreshold(groupThreshold);
    op->setMaxEdgeError(maxEdgeError);
    op->setRemoveDegenerateAndRedundantTriangles(removeDegenerate);

    osgwTools::GeometryModifier gm( op );
    model->accept( gm );


    // optimize the scene graph, remove redundant nodes and state etc.
    osgUtil::Optimizer optimizer;
    optimizer.optimize(model.get());

    osgDB::writeNodeFile( *model, fileNameOut);

    return( 0 );
}



/** \page osgwreducer The osgwreducer Application
osgwreducer runs the Reducer GeometryOperation on the specified
input model, and writes the processed model to disk.

For each osg::Geometry object in the input model, osgwtri
performs the following modifications:
\li All GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS, and
GL_QUAD_STRIP PrimitiveSets are converted to plain GL_TRIANGLES.
\li All DrawArrays, DrawElementsUByte, and DrawElementsUShort
PrimitiveSets are converted to DrawElementsUInt.
\li Multiple DrawElementsUInt / GL_TRIANGLES PrimitiveSets
are combined into a single DrawElementsUInt / GL_TRIANGLES
PrimitiveSet.

*/
