HEADERS = graphicsscene.h \
    component.h \
    connection.h \
    pin.h \
    mainwindow.h
SOURCES = graphicsscene.cpp \
    component.cpp \
    connection.cpp \
    pin.cpp \
    mainwindow.cpp \
    main.cpp
RESOURCES = diagramscene.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/graphicsview/diagramscene
sources.files = $$SOURCES \
    $$HEADERS \
    $$RESOURCES \
    $$FORMS \
    diagramscene.pro \
    images
sources.path = $$[QT_INSTALL_EXAMPLES]/graphicsview/diagramscene
INSTALLS += target \
    sources
