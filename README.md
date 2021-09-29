# WeizenbierGame

C++ ���� Actor Model�� ������� ������ ���� ���� ���� ������Ʈ �Դϴ�.

�׽�Ʈ�� ���� ���� Ŭ���̾�Ʈ�� ���� �����մϴ�.

## Dependencies

�ش� ������Ʈ���� ����ϴ� �ܺ� ���̺귯���� �����ϰ� �Ұ��մϴ�. �Ʒ� ���̺귯������ ��ü������ ���ԵǾ� �����Ƿ� ��ġ�� ���� ������ ������ �ʿ�����ϴ�.

### CAF: the C++ Actor Framework
Scala ����� Akka, .Net ����� Akka.net �� ���� C++ ȯ�濡�� Actor Model �� �����ϴ� ���̺귯�� �Դϴ�.

* Homepage: https://www.actor-framework.org/
* Source Code(GitHub Repository): https://github.com/actor-framework/actor-framework

### protobuf
���α׷��� ���, �÷���(OS ȯ��) ���ο� ������� Ȯ�强 ���� ��� ����� �����ϴ� ���̺귯�� �Դϴ�.

* Homepage: https://developers.google.com/protocol-buffers/
* Source Code(GitHub Repository): https://github.com/protocolbuffers/protobuf

## ���� ȯ��

* OS: Windows 
* IDE: Visual Studio 2019

## ����

### ����
* x64/Debug(Ȥ�� Release)/ServerLauncher.exe ����
* listen ��Ʈ�� ������ �� �ִ� -p �ɼ� ����
* ��ɾ� ��: ServerLauncher.exe -p 4242 -> 4242�� ��Ʈ�� ������ ����
* ![serverlauncherexecute](image/readme/serverlauncherexecute.png)

### �׽�Ʈ Ŭ���̾�Ʈ
* x64/Debug(Ȥ�� Release)/TestClient.exe ����
* ���� ��� ������ ��Ʈ�� ������ �� �ִ� -p �ɼ� ����
* ![testclientexecute](image/readme/testclientexecute.png)

#### ��ɺ� �������� �׽�Ʈ ���(�⺻ ���)
* ������ ������ �������� ����� Ȯ���ϱ� ���� ���
* ��ɾ� ��: TestClient.exe -p 4242 -> 4242�� ��Ʈ ������ ���� �õ�
* '/help' ��ɾ�� �������� ��� ���� �� ��ɾ� Ȯ��
* ![testclienthelp](image/readme/testclienthelp.png)

#### Bot ���� ���
* ������ �ټ��� Bot(���� Ŭ���̾�Ʈ)�� �����Ͽ� ���ϸ� �����ϱ� ���� ���, ���� Ȯ�� ����
* -b �ɼ����� Bot�� ������ �����ؾ߸� �ش� ���� ����
* ��ɾ� ��: TestClient.exe -p 4242 -b 1000 -> 4242�� ��Ʈ ������ 1000���� Bot ���� �õ�
* ![testclientbotmodeexecute](image/readme/testclientbotmodeexecute.png)