#include <string>

int saveDb(wxString rootDir, wxFrame *p);

int deletePhotoBatch(const int execID, wxFrame *p);

int updateBatch(const int execID, const int keepPriority, wxFrame *frame);

int getHistory(wxFrame *frame);

int getRepeat(wxFrame *frame);

int CodePageConvert(uint32_t uDestCodePage, void *pDestChar, uint32_t uSrcCodePage, void *pSrcChar);