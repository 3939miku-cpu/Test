/*
 * 成绩管理系统（改进版）
 * 学号：032580219
 * 姓名：王徐嘉
 * 完成日期：2026 年 6 月 15 日
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ==================== 数据结构定义 ==================== */

typedef struct {
    char xh[10];
    char xm[20];
    char xb[3];
    int nl;
} Student;

typedef struct {
    char kh[10];
    char km[25];
    float xf;
} Course;

typedef struct {
    char xh[10];
    char kh[10];
    float cj;
} Select;

typedef struct {
    char xh[10];
    char xm[20];
    float cj[30];
    char grade[30];
    float zpj;
    float zxf;
} Score;

/* ==================== 全局常量 ==================== */

#define MAX_STUDENT 100
#define MAX_COURSE 50
#define MAX_SELECT 500
#define MAX_SCORE 100

/* ==================== 函数声明 ==================== */

void init(Student slist[], int *scount, Course clist[], int *ccount, 
          Select sclist[], int *sccount);
int create_cjlist(Select sclist[], int sccount, Course clist[], int ccount, 
                  Score cjlist[]);
void disp_stud(Student slist[], int scount);
void disp_course(Course clist[], int ccount);
void disp_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, 
                 Student slist[], int scount);
void sort_slist(Student slist[], int scount);
void sort_clist(Course clist[], int ccount);
void sort_cjlist(Score cjlist[], int cjcount);
int input_stud(Student slist[], int scount);
int input_course(Course clist[], int ccount);
int input_select(Select sclist[], int sccount);
int delete_stud(Student slist[], int scount);
int delete_course(Course clist[], int ccount);
int delete_select(Select sclist[], int sccount);
void query_stud(Student slist[], int scount);
void query_course(Course clist[], int ccount);
void query_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, 
                  Student slist[], int scount);
void write_to_file1(Student slist[], int scount, Course clist[], int ccount, 
                    Select sclist[], int sccount);
void write_to_file2(Score cjlist[], int cjcount, Course clist[], int ccount, 
                    Student slist[], int scount);

/* ==================== 改进功能函数 ==================== */

char getGrade(float score) {
    if (score >= 90) return 'A';
    else if (score >= 80) return 'B';
    else if (score >= 70) return 'C';
    else if (score >= 60) return 'D';
    else return 'F';
}

void show_grade_distribution(Score cjlist[], int cjcount) {
    int ranges[5] = {0};
    int i, j;
    
    for (i = 0; i < cjcount; i++) {
        if (cjlist[i].zpj >= 90) ranges[0]++;
        else if (cjlist[i].zpj >= 80) ranges[1]++;
        else if (cjlist[i].zpj >= 70) ranges[2]++;
        else if (cjlist[i].zpj >= 60) ranges[3]++;
        else ranges[4]++;
    }
    
    printf("\n");
    printf("+----------------------------------------+\n");
    printf("|         成绩分布直方图                 |\n");
    printf("+----------------------------------------+\n");
    printf("|  90-100: ");
    for (j = 0; j < ranges[0]; j++) printf("*");
    printf(" (%d人)\n", ranges[0]);
    
    printf("|  80-89 : ");
    for (j = 0; j < ranges[1]; j++) printf("*");
    printf(" (%d人)\n", ranges[1]);
    
    printf("|  70-79 : ");
    for (j = 0; j < ranges[2]; j++) printf("*");
    printf(" (%d人)\n", ranges[2]);
    
    printf("|  60-69 : ");
    for (j = 0; j < ranges[3]; j++) printf("*");
    printf(" (%d人)\n", ranges[3]);
    
    printf("|  <60   : ");
    for (j = 0; j < ranges[4]; j++) printf("*");
    printf(" (%d人)\n", ranges[4]);
    printf("+----------------------------------------+\n");
}

void analyze_course(Course clist[], int ccount, Select sclist[], int sccount) {
    int i, j;
    
    printf("\n");
    printf("+----------------------------------------+\n");
    printf("|         课程统计分析                   |\n");
    printf("+----------------------------------------+\n");
    
    for (i = 0; i < ccount; i++) {
        float sum = 0, max = -1, min = 101;
        int count = 0, pass = 0;
        
        for (j = 0; j < sccount; j++) {
            if (strcmp(sclist[j].kh, clist[i].kh) == 0 && sclist[j].cj >= 0) {
                sum += sclist[j].cj;
                count++;
                if (sclist[j].cj >= 60) pass++;
                if (sclist[j].cj > max) max = sclist[j].cj;
                if (sclist[j].cj < min) min = sclist[j].cj;
            }
        }
        
        if (count > 0) {
            printf("\n[%s]\n", clist[i].km);
            printf("  选考人数：%d 人\n", count);
            printf("  平均分：%.2f 分\n", sum/count);
            printf("  最高分：%.1f 分\n", max);
            printf("  最低分：%.1f 分\n", min);
            printf("  及格率：%.1f%%\n", (float)pass/count*100);
        }
    }
}

/* ==================== 辅助函数 ==================== */

void get_timestamp(char *buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    sprintf(buffer, "%04d%02d%02d%02d%02d%02d", 
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
}

void pause_screen() {
    printf("\n按任意键继续...");
    getchar();
}

int find_student(Student slist[], int scount, char *xh) {
    int i;
    for (i = 0; i < scount; i++) {
        if (strcmp(slist[i].xh, xh) == 0) return i;
    }
    return -1;
}

int find_course(Course clist[], int ccount, char *kh) {
    int i;
    for (i = 0; i < ccount; i++) {
        if (strcmp(clist[i].kh, kh) == 0) return i;
    }
    return -1;
}

/* ==================== 主函数 ==================== */

int main() {
    Student slist[MAX_STUDENT];
    Course clist[MAX_COURSE];
    Select sclist[MAX_SELECT];
    Score cjlist[MAX_SCORE];
    
    int scount = 0, ccount = 0, sccount = 0, cjcount = 0;
    int choice, subchoice;
    
    printf("+----------------------------------------+\n");
    printf("|   成绩管理系统（改进版）               |\n");
    printf("|   学号：032580219  姓名：王徐嘉        |\n");
    printf("|   功能：成绩等级 + 统计分析            |\n");
    printf("+----------------------------------------+\n");
    
    while (1) {
        printf("\n+----------------------------------------+\n");
        printf("|  1.导入初始数据                        |\n");
        printf("|  2.显示信息                            |\n");
        printf("|  3.输入记录                            |\n");
        printf("|  4.删除记录                            |\n");
        printf("|  5.查询信息                            |\n");
        printf("|  6.批量导出数据                        |\n");
        printf("|  7.成绩统计分析  【新增】              |\n");
        printf("|  0.退出                                |\n");
        printf("+----------------------------------------+\n");
        printf("请给出你的选择：");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("输入无效，请输入 0-7 的数字。\n");
            continue;
        }
        getchar();
        
        switch (choice) {
            case 1:
                init(slist, &scount, clist, &ccount, sclist, &sccount);
                cjcount = create_cjlist(sclist, sccount, clist, ccount, cjlist);
                printf("数据导入成功！学生：%d 人，课程：%d 门，选课：%d 条\n", 
                       scount, ccount, sccount);
                break;
            case 2:
                printf("\n+----------------------------------------+\n");
                printf("|  1.显示学生信息                        |\n");
                printf("|  2.显示课程信息                        |\n");
                printf("|  3.显示成绩单                          |\n");
                printf("|  4.成绩分布直方图  【新增】            |\n");
                printf("|  0.返回主菜单                          |\n");
                printf("+----------------------------------------+\n");
                printf("请选择：");
                scanf("%d", &subchoice);
                getchar();
                
                if (subchoice == 1) { 
                    sort_slist(slist, scount); 
                    disp_stud(slist, scount); 
                } else if (subchoice == 2) { 
                    sort_clist(clist, ccount); 
                    disp_course(clist, ccount); 
                } else if (subchoice == 3) { 
                    sort_cjlist(cjlist, cjcount); 
                    disp_cjlist(cjlist, cjcount, clist, ccount, slist, scount); 
                } else if (subchoice == 4) {
                    show_grade_distribution(cjlist, cjcount);
                }
                break;
            case 3:
                printf("\n+----------------------------------------+\n");
                printf("|  1.输入学生信息                        |\n");
                printf("|  2.输入课程信息                        |\n");
                printf("|  3.输入选课信息                        |\n");
                printf("|  0.返回主菜单                          |\n");
                printf("+----------------------------------------+\n");
                printf("请选择：");
                scanf("%d", &subchoice);
                getchar();
                
                if (subchoice == 1) scount = input_stud(slist, scount);
                else if (subchoice == 2) ccount = input_course(clist, ccount);
                else if (subchoice == 3) {
                    sccount = input_select(sclist, sccount);
                    cjcount = create_cjlist(sclist, sccount, clist, ccount, cjlist);
                }
                break;
            case 4:
                printf("\n+----------------------------------------+\n");
                printf("|  1.删除学生记录                        |\n");
                printf("|  2.删除课程记录                        |\n");
                printf("|  3.删除选课记录                        |\n");
                printf("|  0.返回主菜单                          |\n");
                printf("+----------------------------------------+\n");
                printf("请选择：");
                scanf("%d", &subchoice);
                getchar();
                
                if (subchoice == 1) scount = delete_stud(slist, scount);
                else if (subchoice == 2) ccount = delete_course(clist, ccount);
                else if (subchoice == 3) {
                    sccount = delete_select(sclist, sccount);
                    cjcount = create_cjlist(sclist, sccount, clist, ccount, cjlist);
                }
                break;
            case 5:
                printf("\n+----------------------------------------+\n");
                printf("|  1.查询学生信息                        |\n");
                printf("|  2.查询课程信息                        |\n");
                printf("|  3.查询成绩单                          |\n");
                printf("|  0.返回主菜单                          |\n");
                printf("+----------------------------------------+\n");
                printf("请选择：");
                scanf("%d", &subchoice);
                getchar();
                
                if (subchoice == 1) query_stud(slist, scount);
                else if (subchoice == 2) query_course(clist, ccount);
                else if (subchoice == 3) query_cjlist(cjlist, cjcount, clist, ccount, slist, scount);
                break;
            case 6:
                write_to_file1(slist, scount, clist, ccount, sclist, sccount);
                write_to_file2(cjlist, cjcount, clist, ccount, slist, scount);
                printf("数据导出成功！\n");
                break;
            case 7:
                analyze_course(clist, ccount, sclist, sccount);
                break;
            case 0:
                printf("感谢使用，再见！\n");
                return 0;
            default:
                printf("无效选择，请输入 0-7 的数字。\n");
        }
    }
}

/* ==================== 功能函数实现 ==================== */

void init(Student slist[], int *scount, Course clist[], int *ccount, 
          Select sclist[], int *sccount) {
    char filename[50];
    FILE *fp;
    
    *scount = 0; *ccount = 0; *sccount = 0;
    
    printf("请输入学生数据文件名（直接回车使用 student.txt）：");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    if (strlen(filename) == 0) strcpy(filename, "student.txt");
    
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("未找到学生数据文件，使用空数据。\n");
    } else {
        while (fscanf(fp, "%s %s %s %d", slist[*scount].xh, 
                      slist[*scount].xm, slist[*scount].xb, &slist[*scount].nl) != EOF) {
            (*scount)++;
            if (*scount >= MAX_STUDENT) break;
        }
        fclose(fp);
        printf("已读取 %d 条学生记录。\n", *scount);
    }
    
    printf("请输入课程数据文件名（直接回车使用 course.txt）：");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    if (strlen(filename) == 0) strcpy(filename, "course.txt");
    
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("未找到课程数据文件，使用空数据。\n");
    } else {
        while (fscanf(fp, "%s %s %f", clist[*ccount].kh, 
                      clist[*ccount].km, &clist[*ccount].xf) != EOF) {
            (*ccount)++;
            if (*ccount >= MAX_COURSE) break;
        }
        fclose(fp);
        printf("已读取 %d 条课程记录。\n", *ccount);
    }
    
    printf("请输入选课数据文件名（直接回车使用 select.txt）：");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    if (strlen(filename) == 0) strcpy(filename, "select.txt");
    
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("未找到选课数据文件，使用空数据。\n");
    } else {
        while (fscanf(fp, "%s %s %f", sclist[*sccount].xh, 
                      sclist[*sccount].kh, &sclist[*sccount].cj) != EOF) {
            (*sccount)++;
            if (*sccount >= MAX_SELECT) break;
        }
        fclose(fp);
        printf("已读取 %d 条选课记录。\n", *sccount);
    }
}

int create_cjlist(Select sclist[], int sccount, Course clist[], int ccount, 
                  Score cjlist[]) {
    int cjcount = 0;
    char xhs[MAX_SCORE][10];
    int xhcount = 0;
    int i, j;
    
    for (i = 0; i < sccount; i++) {
        int found = 0;
        for (j = 0; j < xhcount; j++) {
            if (strcmp(xhs[j], sclist[i].xh) == 0) { found = 1; break; }
        }
        if (!found && xhcount < MAX_SCORE) {
            strcpy(xhs[xhcount++], sclist[i].xh);
        }
    }
    
    for (i = 0; i < xhcount; i++) {
        strcpy(cjlist[cjcount].xh, xhs[i]);
        cjlist[cjcount].xm[0] = '\0';
        cjlist[cjcount].zpj = 0;
        cjlist[cjcount].zxf = 0;
        
        for (j = 0; j < 30; j++) {
            cjlist[cjcount].cj[j] = -1;
            cjlist[cjcount].grade[j] = ' ';
        }
        
        for (j = 0; j < sccount; j++) {
            if (strcmp(sclist[j].xh, xhs[i]) == 0) {
                int course_idx = find_course(clist, ccount, sclist[j].kh);
                if (course_idx >= 0 && course_idx < 30) {
                    cjlist[cjcount].cj[course_idx] = sclist[j].cj;
                    if (sclist[j].cj >= 0) {
                        cjlist[cjcount].zpj += sclist[j].cj * clist[course_idx].xf;
                        cjlist[cjcount].zxf += clist[course_idx].xf;
                        cjlist[cjcount].grade[course_idx] = getGrade(sclist[j].cj);
                    }
                }
            }
        }
        
        if (cjlist[cjcount].zxf > 0) {
            cjlist[cjcount].zpj /= cjlist[cjcount].zxf;
        }
        
        cjcount++;
    }
    
    return cjcount;
}

void sort_slist(Student slist[], int scount) {
    int i, j;
    for (i = 0; i < scount - 1; i++) {
        for (j = i + 1; j < scount; j++) {
            if (strcmp(slist[i].xh, slist[j].xh) > 0) {
                Student temp = slist[i];
                slist[i] = slist[j];
                slist[j] = temp;
            }
        }
    }
}

void sort_clist(Course clist[], int ccount) {
    int i, j;
    for (i = 0; i < ccount - 1; i++) {
        for (j = i + 1; j < ccount; j++) {
            if (strcmp(clist[i].kh, clist[j].kh) > 0) {
                Course temp = clist[i];
                clist[i] = clist[j];
                clist[j] = temp;
            }
        }
    }
}

void sort_cjlist(Score cjlist[], int cjcount) {
    int i, j;
    for (i = 0; i < cjcount - 1; i++) {
        for (j = i + 1; j < cjcount; j++) {
            if (cjlist[i].zpj < cjlist[j].zpj) {
                Score temp = cjlist[i];
                cjlist[i] = cjlist[j];
                cjlist[j] = temp;
            }
        }
    }
}

void disp_stud(Student slist[], int scount) {
    int i;
    if (scount == 0) { printf("暂无学生记录。\n"); return; }
    
    printf("\n%-12s %-20s %-6s %-6s\n", "学号", "姓名", "性别", "年龄");
    printf("----------------------------------------------------\n");
    
    for (i = 0; i < scount; i++) {
        printf("%-12s %-20s %-6s %-6d\n", slist[i].xh, slist[i].xm, 
               slist[i].xb, slist[i].nl);
        if ((i + 1) % 10 == 0 && i < scount - 1) pause_screen();
    }
}

void disp_course(Course clist[], int ccount) {
    int i;
    if (ccount == 0) { printf("暂无课程记录。\n"); return; }
    
    printf("\n%-12s %-25s %-8s\n", "课号", "课名", "学分");
    printf("----------------------------------------------------\n");
    
    for (i = 0; i < ccount; i++) {
        printf("%-12s %-25s %-8.1f\n", clist[i].kh, clist[i].km, clist[i].xf);
        if ((i + 1) % 10 == 0 && i < ccount - 1) pause_screen();
    }
}

void disp_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, 
                 Student slist[], int scount) {
    int i, j, k;
    if (cjcount == 0) { printf("暂无成绩记录。\n"); return; }
    
    printf("\n%-6s %-10s %-12s %-8s %-8s %-8s", "排名", "学号", "姓名", "总学分", "平均分", "等级");
    for (i = 0; i < ccount && i < 3; i++) {
        printf(" %-6s", clist[i].km);
    }
    printf("\n");
    printf("================================================================================\n");
    
    for (i = 0; i < cjcount; i++) {
        for (k = 0; k < scount; k++) {
            if (strcmp(slist[k].xh, cjlist[i].xh) == 0) {
                strcpy(cjlist[i].xm, slist[k].xm);
                break;
            }
        }
        
        printf("%-6d %-10s %-12s %-8.1f %-8.2f %-8c", i + 1, cjlist[i].xh, 
               cjlist[i].xm, cjlist[i].zxf, cjlist[i].zpj, getGrade(cjlist[i].zpj));
        for (j = 0; j < ccount && j < 3; j++) {
            if (cjlist[i].cj[j] >= 0) 
                printf(" %-6.1f", cjlist[i].cj[j]);
            else 
                printf(" %-6s", "-");
        }
        printf("\n");
        if ((i + 1) % 10 == 0 && i < cjcount - 1) pause_screen();
    }
}

int input_stud(Student slist[], int scount) {
    char choice;
    do {
        Student new_stud;
        int idx;
        printf("\n请输入学生信息：\n");
        printf("学号："); scanf("%s", new_stud.xh); getchar();
        
        idx = find_student(slist, scount, new_stud.xh);
        if (idx >= 0) {
            printf("该学号已存在！是否替换？(y/n)：");
            scanf("%c", &choice); getchar();
            if (choice == 'y' || choice == 'Y') {
                printf("姓名："); scanf("%s", slist[idx].xm); getchar();
                printf("性别："); scanf("%s", slist[idx].xb); getchar();
                printf("年龄："); scanf("%d", &slist[idx].nl); getchar();
                printf("记录已更新。\n");
            }
        } else {
            if (scount >= MAX_STUDENT) { printf("学生记录已达上限！\n"); break; }
            printf("姓名："); scanf("%s", new_stud.xm); getchar();
            printf("性别："); scanf("%s", new_stud.xb); getchar();
            printf("年龄："); scanf("%d", &new_stud.nl); getchar();
            slist[scount++] = new_stud;
            printf("记录已添加。\n");
        }
        
        printf("是否继续输入？(y/n)："); scanf("%c", &choice); getchar();
    } while (choice == 'y' || choice == 'Y');
    return scount;
}

int input_course(Course clist[], int ccount) {
    char choice;
    do {
        Course new_course;
        int idx;
        printf("\n请输入课程信息：\n");
        printf("课号："); scanf("%s", new_course.kh); getchar();
        
        idx = find_course(clist, ccount, new_course.kh);
        if (idx >= 0) {
            printf("该课号已存在！是否替换？(y/n)：");
            scanf("%c", &choice); getchar();
            if (choice == 'y' || choice == 'Y') {
                printf("课名："); scanf("%s", clist[idx].km); getchar();
                printf("学分："); scanf("%f", &clist[idx].xf); getchar();
                printf("记录已更新。\n");
            }
        } else {
            if (ccount >= MAX_COURSE) { printf("课程记录已达上限！\n"); break; }
            printf("课名："); scanf("%s", new_course.km); getchar();
            printf("学分："); scanf("%f", &new_course.xf); getchar();
            clist[ccount++] = new_course;
            printf("记录已添加。\n");
        }
        
        printf("是否继续输入？(y/n)："); scanf("%c", &choice); getchar();
    } while (choice == 'y' || choice == 'Y');
    return ccount;
}

int input_select(Select sclist[], int sccount) {
    char choice;
    do {
        Select new_select;
        int i, exists = 0;
        printf("\n请输入选课信息：\n");
        printf("学号："); scanf("%s", new_select.xh); getchar();
        printf("课号："); scanf("%s", new_select.kh); getchar();
        printf("成绩（-1 表示无成绩）："); scanf("%f", &new_select.cj); getchar();
        
        if (new_select.cj < -1 || new_select.cj > 120) {
            printf("错误：成绩必须在 -1 到 120 之间！\n");
            continue;
        }
        
        for (i = 0; i < sccount; i++) {
            if (strcmp(sclist[i].xh, new_select.xh) == 0 && 
                strcmp(sclist[i].kh, new_select.kh) == 0) {
                printf("该选课记录已存在！是否替换？(y/n)：");
                scanf("%c", &choice); getchar();
                if (choice == 'y' || choice == 'Y') { sclist[i] = new_select; printf("记录已更新。\n"); }
                exists = 1;
                break;
            }
        }
        
        if (!exists) {
            if (sccount >= MAX_SELECT) { printf("选课记录已达上限！\n"); break; }
            sclist[sccount++] = new_select;
            printf("记录已添加。\n");
        }
        
        printf("是否继续输入？(y/n)："); scanf("%c", &choice); getchar();
    } while (choice == 'y' || choice == 'Y');
    return sccount;
}

int delete_stud(Student slist[], int scount) {
    char key[20];
    char choice;
    int found = 0;
    int i;
    
    printf("请输入要删除的学生学号或姓名："); scanf("%s", key); getchar();
    
    for (i = 0; i < scount; ) {
        if (strcmp(slist[i].xh, key) == 0 || strcmp(slist[i].xm, key) == 0) {
            printf("找到：%s %s %s %d\n", slist[i].xh, slist[i].xm, slist[i].xb, slist[i].nl);
            printf("是否删除？(y/n)："); scanf("%c", &choice); getchar();
            if (choice == 'y' || choice == 'Y') {
                int j;
                for (j = i; j < scount - 1; j++) slist[j] = slist[j + 1];
                scount--; found = 1;
                printf("记录已删除。\n");
            } else i++;
        } else i++;
    }
    
    if (!found) printf("未找到匹配的记录。\n");
    return scount;
}

int delete_course(Course clist[], int ccount) {
    char key[25];
    char choice;
    int found = 0;
    int i;
    
    printf("请输入要删除的课程课号或课名："); scanf("%s", key); getchar();
    
    for (i = 0; i < ccount; ) {
        if (strcmp(clist[i].kh, key) == 0 || strcmp(clist[i].km, key) == 0) {
            printf("找到：%s %s %.1f\n", clist[i].kh, clist[i].km, clist[i].xf);
            printf("是否删除？(y/n)："); scanf("%c", &choice); getchar();
            if (choice == 'y' || choice == 'Y') {
                int j;
                for (j = i; j < ccount - 1; j++) clist[j] = clist[j + 1];
                ccount--; found = 1;
                printf("记录已删除。\n");
            } else i++;
        } else i++;
    }
    
    if (!found) printf("未找到匹配的记录。\n");
    return ccount;
}

int delete_select(Select sclist[], int sccount) {
    char key[10];
    char choice;
    int found = 0;
    int i;
    
    printf("请输入要删除选课记录的学生学号："); scanf("%s", key); getchar();
    
    for (i = 0; i < sccount; ) {
        if (strcmp(sclist[i].xh, key) == 0) {
            printf("找到：%s %s %.1f\n", sclist[i].xh, sclist[i].kh, sclist[i].cj);
            printf("是否删除？(y/n)："); scanf("%c", &choice); getchar();
            if (choice == 'y' || choice == 'Y') {
                int j;
                for (j = i; j < sccount - 1; j++) sclist[j] = sclist[j + 1];
                sccount--; found = 1;
                printf("记录已删除。\n");
            } else i++;
        } else i++;
    }
    
    if (!found) printf("未找到匹配的记录。\n");
    return sccount;
}

void query_stud(Student slist[], int scount) {
    char key[20];
    int found = 0;
    int i;
    
    printf("请输入要查询的学生学号或姓名："); scanf("%s", key); getchar();
    
    printf("\n%-12s %-20s %-6s %-6s\n", "学号", "姓名", "性别", "年龄");
    printf("----------------------------------------------------\n");
    
    for (i = 0; i < scount; i++) {
        if (strcmp(slist[i].xh, key) == 0 || strcmp(slist[i].xm, key) == 0) {
            printf("%-12s %-20s %-6s %-6d\n", slist[i].xh, slist[i].xm, 
                   slist[i].xb, slist[i].nl);
            found = 1;
        }
    }
    if (!found) printf("未找到匹配的记录。\n");
}

void query_course(Course clist[], int ccount) {
    char key[25];
    int found = 0;
    int i;
    
    printf("请输入要查询的课程课号或课名："); scanf("%s", key); getchar();
    
    printf("\n%-12s %-25s %-8s\n", "课号", "课名", "学分");
    printf("----------------------------------------------------\n");
    
    for (i = 0; i < ccount; i++) {
        if (strcmp(clist[i].kh, key) == 0 || strcmp(clist[i].km, key) == 0) {
            printf("%-12s %-25s %-8.1f\n", clist[i].kh, clist[i].km, clist[i].xf);
            found = 1;
        }
    }
    if (!found) printf("未找到匹配的记录。\n");
}

void query_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, 
                  Student slist[], int scount) {
    char key[10];
    int found = 0;
    int i, j, k;
    
    printf("请输入要查询成绩的学生学号："); scanf("%s", key); getchar();
    
    for (i = 0; i < cjcount; i++) {
        if (strcmp(cjlist[i].xh, key) == 0) {
            for (k = 0; k < scount; k++) {
                if (strcmp(slist[k].xh, cjlist[i].xh) == 0) {
                    strcpy(cjlist[i].xm, slist[k].xm);
                    break;
                }
            }
            
            printf("\n+----------------------------------------+\n");
            printf("|              成  绩  单                 |\n");
            printf("+----------------------------------------+\n");
            printf("|  学号：%-24s        |\n", cjlist[i].xh);
            printf("|  姓名：%-24s        |\n", cjlist[i].xm);
            printf("|  总学分：%-15.1f               |\n", cjlist[i].zxf);
            printf("|  加权平均分：%-10.2f             |\n", cjlist[i].zpj);
            printf("|  平均等级：%-15c               |\n", getGrade(cjlist[i].zpj));
            printf("|  排名：第 %-5d 名                       |\n", i + 1);
            printf("+----------------------------------------+\n");
            printf("|  各科成绩：                            |\n");
            for (j = 0; j < ccount; j++) {
                if (cjlist[i].cj[j] >= 0) {
                    printf("|    %s：%.1f 分 (等级：%c)          |\n", 
                           clist[j].km, cjlist[i].cj[j], getGrade(cjlist[i].cj[j]));
                }
            }
            printf("+----------------------------------------+\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("未找到该学生的成绩记录。\n");
}

void write_to_file1(Student slist[], int scount, Course clist[], int ccount, 
                    Select sclist[], int sccount) {
    char timestamp[20], filename[50];
    FILE *fp;
    int i;
    
    get_timestamp(timestamp);
    
    sprintf(filename, "student%s.txt", timestamp);
    fp = fopen(filename, "w");
    if (fp) {
        for (i = 0; i < scount; i++)
            fprintf(fp, "%s %s %s %d\n", slist[i].xh, slist[i].xm, slist[i].xb, slist[i].nl);
        fclose(fp);
        printf("学生信息已导出到：%s\n", filename);
    }
    
    sprintf(filename, "course%s.txt", timestamp);
    fp = fopen(filename, "w");
    if (fp) {
        for (i = 0; i < ccount; i++)
            fprintf(fp, "%s %s %.1f\n", clist[i].kh, clist[i].km, clist[i].xf);
        fclose(fp);
        printf("课程信息已导出到：%s\n", filename);
    }
    
    sprintf(filename, "select%s.txt", timestamp);
    fp = fopen(filename, "w");
    if (fp) {
        for (i = 0; i < sccount; i++)
            fprintf(fp, "%s %s %.1f\n", sclist[i].xh, sclist[i].kh, sclist[i].cj);
        fclose(fp);
        printf("选课信息已导出到：%s\n", filename);
    }
}

void write_to_file2(Score cjlist[], int cjcount, Course clist[], int ccount, 
                    Student slist[], int scount) {
    char timestamp[20], filename[50];
    FILE *fp;
    int i, j;
    
    get_timestamp(timestamp);
    sprintf(filename, "score%s.txt", timestamp);
    
    fp = fopen(filename, "w");
    if (fp) {
        fprintf(fp, "排名 学号 姓名 性别 总学分 平均分 等级");
        for (i = 0; i < ccount; i++) fprintf(fp, " %s", clist[i].km);
        fprintf(fp, "\n");
        
        for (i = 0; i < cjcount; i++) {
            char xb[3] = "-";
            for (j = 0; j < scount; j++) {
                if (strcmp(slist[j].xh, cjlist[i].xh) == 0) {
                    strcpy(xb, slist[j].xb);
                    break;
                }
            }
            
            fprintf(fp, "%d %s %s %s %.1f %.2f %c", i + 1, cjlist[i].xh, 
                    cjlist[i].xm, xb, cjlist[i].zxf, cjlist[i].zpj, getGrade(cjlist[i].zpj));
            for (j = 0; j < ccount; j++) {
                if (cjlist[i].cj[j] >= 0) fprintf(fp, " %.1f", cjlist[i].cj[j]);
                else fprintf(fp, " -");
            }
            fprintf(fp, "\n");
        }
        fclose(fp);
        printf("成绩单已导出到：%s\n", filename);
    }
}
