# Project_AD
使用Visual Studio 2017 编写并运行的一个单变量函数求导工具

## 使用方法(尚未进一步封装，所以非常繁琐)
详见Executive目录下的Executive.cpp的main函数，目前流程如下
+ 实例化一个Tokenizer，记为toker
+ 实例化一个NaiveParser，记为np
+ 将待求导的表达式expression通过toker.setContext(expression)传入toker，参数类型为std::string类型，格式仅包括自变量(例: "x+1", "sin(x)")
+ 调用toker.tokenize()对表达式进行切分，此时表达式会被并存入toker的token_table中
+ 调用np.setExpression(toker.getTokenTable())将toker中的token_table传入np
+ 调用np.inffToSuffix()生成后缀表达式
+ 调用TokenTable tt = np.get_suffix()得到后缀表达式
+ 调用CalculationTree* tree = new Calculation(tt)，生成计算树
+ 调用tree->setVariable_value(variable_name, value)，对单变量函数的自变量进行赋值操作，其中variable_name为std::string类型, value为浮点型
+ 通过std::cout<<tree->diff(tree->root)查看单变量函数在自变量取值value处的导数值
  
## 目前支持的运算符
+ 目前仅支持四则运算（加，减，乘，除）与 sin, cos以及开平方运算sqrt，详情参考EasyTokenizer下TokenLookUpTable.cpp中的构造函数
+ 如果这份代码的扩展性有我一开始以为的那么强，也许我会逐渐支持更多运算符，但是我已经八个月没有更新过了

## Reference
  Part of the codes from course CSE 687 from Dr. James Fawcett, a former Syracuse University professor who retired in May, 2019
