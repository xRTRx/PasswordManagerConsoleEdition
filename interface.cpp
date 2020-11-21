#include "interface.h"

void toClipboard(const std::string& s) {
//	QApplication::clipboard()->setText(s.c_str());
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(s.c_str());
}

