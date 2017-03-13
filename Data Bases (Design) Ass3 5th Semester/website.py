import sys, os
sys.path.append(os.path.join(os.path.split(os.path.abspath(__file__))[0], 'lib'))
from bottle import route, run, static_file, request
import pymysql as db
import settings
import app

def renderTable(tuples):
    printResult = """<style type='text/css'> h1 {color:red;} h2 {color:blue;} p {color:green;} </style>
    <table border = '1' frame = 'above'>"""

    header='<tr><th>'+'</th><th>'.join([str(x) for x in tuples[0]])+'</th></tr>'
    data='<tr>'+'</tr><tr>'.join(['<td>'+'</td><td>'.join([str(y) for y in row])+'</td>' for row in tuples[1:]])+'</tr>'
        
    printResult += header+data+"</table>"
    return printResult

@route('/searchVisit')
def searchVisitWEB():
    pname = request.query.pname or "Unknown Patient"
    hname = request.query.hname or "Unknown Hospital"
    table = app.searchVisit(pname, hname)
    return "<html><body>" + renderTable(table) + "</body></html>"

@route('/insertVisit')
def insertVisitWEB():
    pid = request.query.pid
    hid = request.query.hid
    date = request.query.date
    diagnosisid = request.query.diagnosisid
    table = app.insertVisit(pid, hid, date, diagnosisid)
    return "<html><body>" + renderTable(table) + "</body></html>"

@route('/selectTopNDiseasesPerHospital')
def selectTopNDiseasesPerHospitalWEB():
    n = request.query.n
    table = app.selectTopNDiseasesPerHospital(n)
    return "<html><body>" + renderTable(table) + "</body></html>"

@route('/traceDiseaseInfections')
def traceDiseaseInfectionsWEB():
    dname = request.query.dname
    table = app.traceDiseaseInfections(dname)
    return "<html><body>" + renderTable(table) + "</body></html>"

@route('/moo')
def index():
    import gzip
    import base64
    return gzip.zlib.decompress(base64.decodestring('''eNqNVNtu2zgQfc9XaFWgIa27c0ETalxgiz70oUWx7WIfAkOgJcpkoBsoKpbR5N87lJysnd0ChSBx\nNHNmeOZCptLU1SqVgher1ChTidXfvXDqdsDvZjCmbdJo1qe1MNzJJde9MOAOpgzeuas0mn03bbF3\naq63qtmpwkhwY/fwL4XaSmMVqzTnzQPvHVWAm7vOAXl9idhn1OU7i4tm4Crtc606szp74NrZOOAU\nbT7UojGh3ZBN6vxYvRXmYyWs2P+5/863X3gtyPkc7ZzexevZh6NPbsEf2saI0ZDzZXFO2dlJ+DCv\nFMr/WJbsLI2eubyQ2gFSZxKQM8vDOZsdSodcJBs6uFuzrJi+GpIrVsMfCctGuI5ZtgcZLdkWUNFb\ndQfl0ORGtQ2hP6aEIRt9AdmebQIYmYZdlGlWwGduZFhWbavJJtKUjQkUC83G5SuLl1BUKyCbYExo\nhOIChu6u8JJ1YNc1Ux7Mwv2/oPsFZMUMsivaPDgIIIN7poUZdOOIILlO1eOj8JLr1f375DZ+YlvR\nHOcwdGE39JJMrDRvirYmdLGMY4o1mU1JHHunZtTQJ1ZiBgpiptJMe0vk6VEMTrBFBnD+PmHX9AOv\nyNFuqiRZTw/sYjYG0HcFyypvWvH1IA7j+IqNaUBsJenbtwQp9lKVhlAfKT2L01b+CEiUh6Wqqm9m\nXwlw9XbDSexPT3hBXRs1vXzPcVIE13+J3EzWnS/p7ex4ojsN9uYmv3FRtRF4SL5iDYgF1O2D+N5a\nF/p/ReBhpRoLGD2bwkL52D+1tp4Hw85/YT0F/EV4+ZvhpR2CVxvIow2yvQfbha1wR2xBeSW0Ie63\nvNXi1nG9o4nMqsg2FyuN444ka4Rn+2B2XyxPy3PmvinL+L/14ToneCqyvZ8kc/BeNWTEyHRxhXW+\nOU7/yb+4QIoVYCttr+CCvZzwtpluuaLdncwsHlAc5NeooXuFSZ6OboQ0steFvQvtbfoTFh22jg==\n'''))
   
@route('/:path')
def callback(path):
    return static_file(path, 'web')

@route('/')
def callback():
    return static_file("index.html", 'web')

run(host='localhost', port=settings.web_port, reloader=True, debug=True)
