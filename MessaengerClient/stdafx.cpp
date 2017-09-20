
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// MessaengerClient.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

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