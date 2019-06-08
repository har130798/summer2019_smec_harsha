import click, os, django, openpyxl

#start settings
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'classproj.settings')
django.setup()

from onlineapp.models import *

def import_student_data(filename : str, sheetname : str):
    wb = openpyxl.load_workbook(filename)
    sheet = wb.get_sheet_by_name(sheetname)
    data = []
    for row in sheet.iter_rows():
        rowdata = []
        for cell in row:
            rowdata.append(cell.value.lower())
        data.append(tuple(rowdata))

    return data[1:]

def import_marks(filename : str):
    wb = openpyxl.load_workbook(filename)
    sheet = wb.active
    marks = []
    c = 0
    for row in sheet.iter_rows():
        if c == 0:
            c += 1
            continue
        rowdata = []
        for cell in row:
            rowdata.append(cell.value)
        rowdata = [rowdata[0].split('_')[2]] + rowdata[1:]
        marks.append(rowdata)

    return marks

@click.group()
def onlinedb():
    pass

@onlinedb.command(help='Imports data from excel files and creates tables')
# @click.argument('dbname', default='precourse_assignment')
def importdata():
    # student_data = import_student_data('students.xlsx', 'Current')
    # college_data = import_student_data('students.xlsx', 'Colleges')
    # marks = import_marks('marks.xlsx')

    try:
        pass
        # for student_marks in marks:
            # print(student_marks)
            # s = Student.objects.get(dbname=student_marks[0])
            # m = MockTest1(
            #             problem1=int(student_marks[1]),
            #             problem2=int(student_marks[2]),
            #             problem3=int(student_marks[3]),
            #             problem4=int(student_marks[4]),
            #             total=int(student_marks[5]),
            #             student=s
            # )
            # m.save()
    except Exception as e:
        print(e)
    # click.echo('Imported data !')

if __name__ == '__main__':
    onlinedb()