#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "hdf5::szip-static" for configuration "Release"
set_property(TARGET hdf5::szip-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::szip-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libszip.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::szip-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::szip-static "${_IMPORT_PREFIX}/lib/libszip.a" )

# Import target "hdf5::szip-shared" for configuration "Release"
set_property(TARGET hdf5::szip-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::szip-shared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libszip.so.2.1.1"
  IMPORTED_SONAME_RELEASE "libszip.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::szip-shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::szip-shared "${_IMPORT_PREFIX}/lib/libszip.so.2.1.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
