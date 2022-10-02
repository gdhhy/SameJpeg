#include <string>
#include "JpegFileMain.h"

int saveDb(wxString rootDir, JpegFileFrame *p);

int deletePhotoBatch(const int execID, JpegFileFrame *p);

int updateBatch(const int execID, const int keepPriority, JpegFileFrame *frame);

int getHistory(JpegFileFrame *frame);

int CodePageConvert(uint32_t uDestCodePage, void *pDestChar, uint32_t uSrcCodePage, void *pSrcChar);