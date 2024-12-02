#include <CUnit/Basic.h>
#include "RVC_software_engineering.h"

// 테스트 함수
void test_turnLeft() {
    turnLeft();
    CU_ASSERT(callPowerOffInterface);   // powerOffInterface 호출 확인
    CU_ASSERT(callTurnLeftInterface);  // turnLeftInterface 호출 확인
    resetTestCondition();
}

void test_turnRight() {
    turnLeft();
    CU_ASSERT(callPowerOffInterface);   // powerOffInterface 호출 확인
    CU_ASSERT(callTurnRightInterface);  // turnLeftInterface 호출 확인
    resetTestCondition();
}


void test_moveForward() {
    moveForward();
    CU_ASSERT(callPowerOnInterface);      // powerOnInterface 호출 확인
    CU_ASSERT(callMoveForwardInterface);  // moveForwardInterface 호출 확인
    resetTestCondition();
}

void test_determineObstacleLocation() {
    bool *obstacleLocations;

    setVenvObstaclesStatus(true, false, true); // front, left, right 설정
    obstacleLocations = determineObstacleLocation();

    CU_ASSERT(obstacleLocations[FRONT]);   // FRONT 장애물 감지
    CU_ASSERT(!obstacleLocations[LEFT]);  // LEFT 장애물 없음
    CU_ASSERT(obstacleLocations[RIGHT]);  // RIGHT 장애물 감지

    free(obstacleLocations); // 동적 메모리 해제
    resetTestCondition();
}

// 메인 함수
int main() {
    // CUnit 초기화
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // 테스트 스위트 생성
    CU_pSuite suite = CU_add_suite("RVC Test Suite", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // 테스트 케이스 추가
    if (!CU_add_test(suite, "Test turnLeft", test_turnLeft) ||
        !CU_add_test(suite, "Test moveForward", test_moveForward) ||
        !CU_add_test(suite, "Test determineObstacleLocation", test_determineObstacleLocation)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // 테스트 실행
    CU_basic_run_tests();

    // CUnit 정리
    CU_cleanup_registry();
    return CU_get_error();
}