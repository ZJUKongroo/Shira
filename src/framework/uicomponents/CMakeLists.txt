declare_module(shira_ui_components)

set(MODULE_ALIAS shira::ui_components)

set(MODULE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/view/abstractmenumodel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/abstractmenumodel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/view/menuitem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/menuitem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/uicomponentsmodule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/uicomponentsmodule.h
)

setup_module()
