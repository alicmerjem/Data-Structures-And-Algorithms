/*
double two_stack_algorithm(std::string expression) {
    Stack<double> values;
    Stack<char> operators;
    
    std::string token;
    std::stringstream ss(expression);
    
    while (getline(ss, token, ' ')) {
        if (token == "(") {
            continue;    
        } else if (token == ")") {
            double num = values.pop();
            char op = operators.pop();

            switch (op) {
                case '+':
                    values.push(num + values.pop());
                    break;
                case '-':
                    values.push(values.pop() - num);
                    break;
                case '*':
                    values.push(num * values.pop());
                    break;
                case '/':
                    values.push(values.pop() / num);
                    break;
                case '^':
                    values.push(std::pow(values.pop(), num));
                    break;
                case '%':
                    values.push(std::fmod(values.pop(), num));
                    break;
                default: ;
            }
        } else if (token == "+" || token == "-" || token == "/" || token == "*"
            || token == "^" || token == "%") {
                operators.push(token[0]);
        } else {
            values.push(stod(token));
        }
    }
    return values.pop();
}
*/