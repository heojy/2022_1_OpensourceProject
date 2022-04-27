# 2022_1_OpensourceProject


calender 기능의 경우
https://cwithvisual.tistory.com/entry/%EB%8B%AC%EB%A0%A5-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8
의 코드를 참고하여, calender.h 파일과 calender.c 파일을 작성하였습니다. 

todolist 기능의 경우 
https://soooprmx.com/c%EB%A1%9C-%EA%B0%84%EB%8B%A8%ED%95%9C-todo%EC%95%B1-%EA%B5%AC%ED%98%84/ 
의 코드를 참고하여, todolist.h 파일과 todolist.c 파일을 작성하였습니다.


가계부 기능을 실행하여 입력한 수입 / 지출 내역은 list.txt에서 확인 할 수 있습니다.
수입 / 지출 내역 입력시 동적 메모리를 활용하여 많은 입력시에도 메모리를 절약할 수 있도록 하였습니다.
내역을 텍스트 파일에 저장하고, 이를 다시 읽어오는 방식으로 작동하므로 프로그램이 종료된 후에도 다시 실행했을 때에도 잔액과 기록을 확인할 수 있습니다.


투두 리스트 기능 또한 가계부 기능처럼 파일에 저장하고 이를 다시 읽어옴으로써 종료 된 뒤에도 재실행시 확인하기 위해 todo.dat 파일이 생성되는데, 
기능을 최초 사용시 종료하기 전까지는 에러가 등장하지 않지만
프로그램을 종료 후 재실행 하거나 기능을 종료 후 재실행 시 해당 파일(todo.dat)과의 충돌로 에러가 뜨는 오류가 있습니다.
생성된 todo.dat 파일을 삭제 후 실행하면 작동 가능합니다.

해당 코드만 독립적으로 실행시 오류가 등장하지 않는데, 다른 기능들과 함께 모았을 때만 오류가 등장하여 원인을 이해하지 못해 해결하지 못하였습니다.





