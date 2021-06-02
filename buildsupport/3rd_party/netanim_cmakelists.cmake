# Copyright (c) 2017-2021 Universidade de Brasília
#
# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public
# License version 2 as published by the Free Software Foundation;
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free
# Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# Author: Gabriel Ferreira <gabrielcarvfer@gmail.com>

find_package(
  Qt4
  COMPONENTS QtGui
  QUIET
)
find_package(
  Qt5
  COMPONENTS Core Widgets PrintSupport Gui
  QUIET
)

if((NOT ${Qt4_FOUND}) AND (NOT ${Qt5_FOUND}))
  message(FATAL_ERROR "You need Qt installed to build NetAnim")
endif()

# Qt 4 requires these inclusions
if(NOT ${Qt5_found})
  include(${QT_USE_FILE})
  add_definitions(${QT_DEFINITIONS})
  include_directories(${QT_INCLUDES})
endif()

# Used by qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(source_files
    main.cpp
    logqt.cpp
    resizeableitem.cpp
    animnode.cpp
    animatorscene.cpp
    animpacket.cpp
    netanim.cpp
    animatormode.cpp
    mode.cpp
    animxmlparser.cpp
    animatorview.cpp
    animlink.cpp
    animresource.cpp
    statsview.cpp
    statsmode.cpp
    routingxmlparser.cpp
    routingstatsscene.cpp
    interfacestatsscene.cpp
    flowmonxmlparser.cpp
    flowmonstatsscene.cpp
    textbubble.cpp
    qtpropertybrowser/src/qtvariantproperty.cpp
    qtpropertybrowser/src/qttreepropertybrowser.cpp
    qtpropertybrowser/src/qtpropertymanager.cpp
    qtpropertybrowser/src/qtpropertybrowserutils.cpp
    qtpropertybrowser/src/qtpropertybrowser.cpp
    qtpropertybrowser/src/qtgroupboxpropertybrowser.cpp
    qtpropertybrowser/src/qteditorfactory.cpp
    qtpropertybrowser/src/qtbuttonpropertybrowser.cpp
    animpropertybrowser.cpp
    qtpropertybrowser/src/filepathmanager.cpp
    qtpropertybrowser/src/fileeditfactory.cpp
    qtpropertybrowser/src/fileedit.cpp
    packetsmode.cpp
    packetsview.cpp
    packetsscene.cpp
    graphpacket.cpp
    table.cpp
    countertablesscene.cpp
    qcustomplot.cpp
    log.cpp
)

set(header_files
    abort.h
    logqt.h
    animatorconstants.h
    resizeableitem.h
    animnode.h
    common.h
    animatorscene.h
    timevalue.h
    animpacket.h
    netanim.h
    animatormode.h
    animatorview.h
    mode.h
    animxmlparser.h
    animevent.h
    animlink.h
    animresource.h
    statsview.h
    statsmode.h
    statisticsconstants.h
    routingxmlparser.h
    routingstatsscene.h
    interfacestatsscene.h
    flowmonxmlparser.h
    flowmonstatsscene.h
    textbubble.h
    qtpropertybrowser/src/QtVariantPropertyManager
    qtpropertybrowser/src/QtVariantProperty
    qtpropertybrowser/src/qtvariantproperty.h
    qtpropertybrowser/src/QtVariantEditorFactory
    qtpropertybrowser/src/QtTreePropertyBrowser
    qtpropertybrowser/src/qttreepropertybrowser.h
    qtpropertybrowser/src/QtTimePropertyManager
    qtpropertybrowser/src/QtTimeEditFactory
    qtpropertybrowser/src/QtStringPropertyManager
    qtpropertybrowser/src/QtSpinBoxFactory
    qtpropertybrowser/src/QtSliderFactory
    qtpropertybrowser/src/QtSizePropertyManager
    qtpropertybrowser/src/QtSizePolicyPropertyManager
    qtpropertybrowser/src/QtSizeFPropertyManager
    qtpropertybrowser/src/QtScrollBarFactory
    qtpropertybrowser/src/QtRectPropertyManager
    qtpropertybrowser/src/QtRectFPropertyManager
    qtpropertybrowser/src/qtpropertymanager.h
    qtpropertybrowser/src/qtpropertybrowserutils_p.h
    qtpropertybrowser/src/qtpropertybrowser.h
    qtpropertybrowser/src/QtProperty
    qtpropertybrowser/src/QtPointPropertyManager
    qtpropertybrowser/src/QtPointFPropertyManager
    qtpropertybrowser/src/QtLocalePropertyManager
    qtpropertybrowser/src/QtLineEditFactory
    qtpropertybrowser/src/QtKeySequencePropertyManager
    qtpropertybrowser/src/QtKeySequenceEditorFactory
    qtpropertybrowser/src/QtIntPropertyManager
    qtpropertybrowser/src/QtGroupPropertyManager
    qtpropertybrowser/src/QtGroupBoxPropertyBrowser
    qtpropertybrowser/src/qtgroupboxpropertybrowser.h
    qtpropertybrowser/src/QtFontPropertyManager
    qtpropertybrowser/src/QtFontEditorFactory
    qtpropertybrowser/src/QtFlagPropertyManager
    qtpropertybrowser/src/QtEnumPropertyManager
    qtpropertybrowser/src/QtEnumEditorFactory
    qtpropertybrowser/src/qteditorfactory.h
    qtpropertybrowser/src/QtDoubleSpinBoxFactory
    qtpropertybrowser/src/QtDoublePropertyManager
    qtpropertybrowser/src/QtDateTimePropertyManager
    qtpropertybrowser/src/QtDateTimeEditFactory
    qtpropertybrowser/src/QtDatePropertyManager
    qtpropertybrowser/src/QtDateEditFactory
    qtpropertybrowser/src/QtCursorPropertyManager
    qtpropertybrowser/src/QtCursorEditorFactory
    qtpropertybrowser/src/QtColorPropertyManager
    qtpropertybrowser/src/QtColorEditorFactory
    qtpropertybrowser/src/QtCheckBoxFactory
    qtpropertybrowser/src/QtCharPropertyManager
    qtpropertybrowser/src/QtCharEditorFactory
    qtpropertybrowser/src/QtButtonPropertyBrowser
    qtpropertybrowser/src/qtbuttonpropertybrowser.h
    qtpropertybrowser/src/QtBrowserItem
    qtpropertybrowser/src/QtBoolPropertyManager
    qtpropertybrowser/src/QtAbstractPropertyManager
    qtpropertybrowser/src/QtAbstractPropertyBrowser
    qtpropertybrowser/src/QtAbstractEditorFactoryBase
    animpropertybrowser.h
    qtpropertybrowser/src/filepathmanager.h
    qtpropertybrowser/src/fileeditfactory.h
    qtpropertybrowser/src/fileedit.h
    packetsmode.h
    packetsview.h
    packetsscene.h
    graphpacket.h
    table.h
    countertablesscene.h
    qcustomplot.h
)

set(resource_files resources.qrc qtpropertybrowser/src/qtpropertybrowser.qrc)

if(WIN32)
  add_executable(netanim WIN32 ${source_files} ${resource_files})
else()
  add_executable(netanim ${source_files} ${resource_files})
endif()

if(Qt4_FOUND)
  target_link_libraries(netanim PUBLIC ${libcore} Qt4::QtGui)
else()
  target_link_libraries(netanim PUBLIC ${libcore} Qt5::Widgets Qt5::Core Qt5::PrintSupport Qt5::Gui)
endif()

target_include_directories(netanim PUBLIC qtpropertybrowser/src)
set_runtime_outputdirectory(netanim ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin)
