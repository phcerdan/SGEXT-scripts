set(SG_MODULE_NAME "Core")
set(SG_MODULE_${SG_MODULE_NAME}_LIBRARY "SG${SG_MODULE_NAME}")
set(SG_LIBRARIES ${SG_LIBRARIES} ${SG_MODULE_${SG_MODULE_NAME}_LIBRARY} PARENT_SCOPE)
set(SG_MODULE_INTERNAL_DEPENDS) # Defined for consistency with other modules
set(SG_MODULE_${SG_MODULE_NAME}_DEPENDS
  ${SG_MODULE_INTERNAL_DEPENDS}
  Boost::graph
  Boost::serialization
  histo)
set(SG_MODULE_${SG_MODULE_NAME}_SOURCES
    bounding_box.cpp
    edge_points_utilities.cpp
    filter_spatial_graph.cpp
    graph_data.cpp
    serialize_spatial_graph.cpp
    shortest_path.cpp
    spatial_graph_utilities.cpp # Deprecated
    spatial_graph_io.cpp
    )
list(TRANSFORM SG_MODULE_${SG_MODULE_NAME}_SOURCES PREPEND "src/")
add_library(${SG_MODULE_${SG_MODULE_NAME}_LIBRARY} ${SG_MODULE_${SG_MODULE_NAME}_SOURCES})
add_library(SGEXT::${SG_MODULE_${SG_MODULE_NAME}_LIBRARY} ALIAS ${SG_MODULE_${SG_MODULE_NAME}_LIBRARY})
target_include_directories(${SG_MODULE_${SG_MODULE_NAME}_LIBRARY} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
target_link_libraries(${SG_MODULE_${SG_MODULE_NAME}_LIBRARY}
  ${SG_MODULE_${SG_MODULE_NAME}_DEPENDS}
  )

if(SG_BUILD_TESTING)
  add_subdirectory(test)
endif()

install(TARGETS ${SG_MODULE_${SG_MODULE_NAME}_LIBRARY}
        EXPORT SGEXTTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtime
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development
        )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sgext
  PATTERN "*.txt" EXCLUDE)

# Append to _targets_to_export in the PARENT_SCOPE.
set(_targets_to_export ${_targets_to_export} ${SG_MODULE_${SG_MODULE_NAME}_LIBRARY} PARENT_SCOPE)
