#!/usr/bin/env node
/* 
 * 对目录下的数据进行简单的 diff 评测
 * */

const fse = require("fs-extra")
const pathFn = require("path")
const {execSync:exec} = require("child_process")



const result_out_path = '/tmp/r_test_out'
var main = '1'
var data_path = 'data'

const log = console.log

const TestCase = require("../libs/testCase_Class.js")

const tc = new TestCase()

let argv = process.argv

if(argv[2])
    main  = argv[2]

if( argv[3])
    data_path = argv[3]



let combine_list = tc.testListByPath(data_path)

for( let item of combine_list){
    let _in = pathFn.join(data_path,item[0])
    let _out = pathFn.join(data_path,item[1])
    exec(`./${main} < ${_in} > ${result_out_path}`)
    try{
        let diff = exec(`diff --strip-trailing-cr ${result_out_path} ${_out}`)
        //log(`diff <( sed -e '$a\\'  ${result_out_path} ) <( sed -e '$a\\'  ${_out} )`)
    }
    catch(e){
        log(`${_in}`)
        log(e.output.toString('utf-8'))
        break;
    }
    //log(diff.toString('utf-8'))
}
