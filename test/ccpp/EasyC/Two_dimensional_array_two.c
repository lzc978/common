#include <stdio.h>

// 各科的平均成绩|各科不及格的人数

int main()
{
    //二维数组：  五行、三列
	//行代表人：  老大到老五
	//列代表科目：语、数、外
	float a[5][3] = { { 80, 75, 56 }, { 59, 65, 71 }, { 59, 63, 70 }, { 85, 45, 90 }, { 76, 77, 45 } };
    int i, j, person_low[3] = {0};
    float s = 0, lesson_aver[3] = {0};

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 5; j++)
        {
            // 先求各科总分/人数
            s = s + a[j][i];
            // 筛选每科不及格人数
            /*
            if (a[j][i] < 60)
            {
                person_low[i]++;
            }
            */
            person_low[i] += a[j][i] < 60 ? 1 : 0;
        }
        lesson_aver[i] = s / (sizeof(a) / sizeof(a[0]));s = 0;
    }
    printf("各科的平均成绩:\n");
	for (i = 0; i < 3; i++)
	{
		printf("%.2f\n", lesson_aver[i]);
	}
		
	printf("各科不及格的人数:\n");
	for (i = 0; i < 3; i++)
	{
		printf("%d\n", person_low[i]);
	}
    return 0;
}