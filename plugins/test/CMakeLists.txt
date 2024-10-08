wasmedge_add_library(wasmedgePluginTest
  SHARED
  testplugin.cc
)

target_compile_options(wasmedgePluginTest
  PUBLIC
  -DWASMEDGE_PLUGIN
)

target_include_directories(wasmedgePluginTest
  PUBLIC
  $<TARGET_PROPERTY:wasmedgePlugin,INCLUDE_DIRECTORIES>
  ${CMAKE_CURRENT_SOURCE_DIR}
)

if(WASMEDGE_LINK_PLUGINS_STATIC)
  target_link_libraries(wasmedgePluginTest
    PRIVATE
    wasmedgeCAPI
  )
else()
  target_link_libraries(wasmedgePluginTest
    PRIVATE
    wasmedge_shared
  )
endif()

install(TARGETS wasmedgePluginTest DESTINATION ${CMAKE_INSTALL_LIBDIR}/wasmedge)