#include "srchilite/langdefmanager.h"
#include "srchilite/instances.h"

int main() {
  // we highlight C++ code for simplicity
  srchilite::SourceHighlighter highlighter
    (srchilite::Instances::getLangDefManager().getHighlightState(
            DATADIR, "cpp.lang"));
