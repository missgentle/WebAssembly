//��Module��ʼ����ϵĹ��Ӷ����м����ִ�е�����
__ATPOSTRUN__.push(() => {
	//����ģ���б�¶����echo����
	Module.ccall('echo', null, ['number'], [10]);
	//Ҳ������������
	Module['asm']['echo'](10);
})