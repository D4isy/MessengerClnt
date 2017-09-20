
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// MessaengerClient.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

int strsplit(CString &src, CString &c, CString *dst, int max)
{
	int cnt = 0;
	int index = src.Find(c);

	while (index != -1 && cnt < max) {
		dst[cnt++] = src.Mid(0, index);
		src = src.Mid(index + c.GetLength(), src.GetLength() - index - c.GetLength());
		index = src.Find(c);
	}

	if (cnt < max) {
		dst[cnt++] = src.Mid(0, src.GetLength());
	}
	return cnt;
}