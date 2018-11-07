if(NS3_NETANIM)
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
            )
    #        qtpropertybrowser/src/QtButtonPropertyBrowser
    #        qtpropertybrowser/src/QtVariantEditorFactory
    #        qtpropertybrowser/src/QtTreePropertyBrowser
    #        qtpropertybrowser/src/QtVariantProperty
    #        qtpropertybrowser/src/QtGroupBoxPropertyBrowser
    #        )

    set(header_files
            abort.h
            assert.h
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

    set(resource_files
            resources.qrc
            qtpropertybrowser/src/qtpropertybrowser.qrc
            )

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    find_package(Qt4 REQUIRED QtGui)

    if(NOT ${Qt4_FOUND})
        message(WARNING You need Qt4 installed to build NetAnim)
    else()
        include(${QT_USE_FILE})
        add_definitions(-DNS3_LOG_ENABLE ${QT_DEFINITIONS})
        include_directories(${QT_INCLUDES} ${CMAKE_BINARY_DIR} qtpropertybrowser/src)

        if(WIN32)
            add_executable(netanim
                    WIN32
                    ${source_files}
                    ${resource_files}
                    )
        else()
            add_executable(netanim
                    ${source_files}
                    ${resource_files}
                    )
        endif()

        target_link_libraries(netanim ${libcore} Qt4::QtGui)
    endif()
endif() #checking if configured to build netanim