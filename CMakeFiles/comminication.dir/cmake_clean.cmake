file(REMOVE_RECURSE
  "libcomminication.pdb"
  "libcomminication.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/comminication.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
