package calculatorPackage;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
public class CalcClass {

	public static void main(String[] args) {
		System.out.println("Enter the equation:");
		Scanner sc = new Scanner(System.in);
		String equation = sc.nextLine();
		char[] operators = {'+', '-', '*', '/', '^', '.', '(', ')', ' '};		
		List<Integer> indexOfOpenBrackets = new ArrayList<>();
		List<Integer> indexOfClosedBrackets = new ArrayList<>();
		for(int i = 0; i < equation.length(); i++)
		{
			if(Character.isDigit(equation.charAt(i)))
				continue;
			for(int j = 0; j < operators.length; j++)
			{				
				if(equation.charAt(i) == operators[j])
					break;
				if(j == operators.length - 1)
				{
					System.err.println("Error, invalid input!");
					return;
				}
					
			}						
		} 
		for(int i = 0; i < equation.length(); i++)
		{
			if(equation.charAt(i) == ')')
				indexOfClosedBrackets.add(i);			
			if(equation.charAt(equation.length() - 1 - i) == '(')
				indexOfOpenBrackets.add(equation.length() - 1 - i);			
		}
		if(indexOfOpenBrackets.size() != indexOfClosedBrackets.size())
		{
			System.err.println("Error, difference between the number of open and closed brakets");
			return;
		}
		System.out.println(CalculateStatement(equation, operators));
	}
	public static double CalculateStatement(String equation, char[] operators)
	{
		List<Double> listOfValues = new ArrayList<Double>();
		List<Character> listOfOperations = new ArrayList<Character>();
		//List<Integer> listOfOpenBrackets = new ArrayList<Integer>();
		//List<Integer> listOfClosedBrackets = new ArrayList<Integer>();
		double decimalsPosition = 0.1;
		double value = 0.0;
		boolean pointFlag = false;
		for(int i = 0; i < equation.length(); i++)
		{	
			if(equation.charAt(i) == ' ')
				continue;
			if(equation.charAt(i) == '.')
			{
				pointFlag = true;
				continue;
			}
			for(int j = 0; j < operators.length; j++)
			{
				if(equation.charAt(i) == operators[j])
				{
					listOfOperations.add(equation.charAt(i));						
					listOfValues.add(value);
					value = 0.0;
					decimalsPosition = 0.1;
					pointFlag = false;					
				}
			}
			if(Character.isDigit(equation.charAt(i)))
			{				
				if(pointFlag)
				{
					value += (double)(equation.charAt(i) - '0') * decimalsPosition;
					decimalsPosition *= 0.1;
				}
				else
				{
					value *= 10.0;
					value += (double)(equation.charAt(i) - '0');
				}
				continue;
			}			
		}
		listOfValues.add(value);		
		for(int i = listOfOperations.size() - 1; i >= 0; i--)
		{
			for(int j = 0; j < listOfOperations.size(); j++)
			{
				if((j > i) && (listOfOperations.get(j) == ')') && (listOfOperations.get(i) == '('))
				{
					CalculateEquation(listOfValues.subList(i, j + 2), listOfOperations.subList(i, j + 1));					
					i = listOfOperations.size() - 1;
					break;
				}
			}
		}
		CalculateEquation(listOfValues, listOfOperations);
		return listOfValues.get(0);
	}
	public static void CalculateEquation(List<Double> v, List<Character> o)
	{
		List<Double> listOfValues = v;
		List<Character> listOfOperations = o; 
		int indexOfOperation = 0;
		char operationWithPriority = ' ';
		for(int i = 0; i < listOfOperations.size(); i++)
		{
			if(listOfOperations.get(i) == '(')
			{
				listOfValues.remove(i);
				listOfOperations.remove(i);
			}
			if(listOfOperations.get(i) == ')')
			{
				listOfValues.remove(i + 1);
				listOfOperations.remove(i);
			}
		}
		while(listOfValues.size() > 1)
		{
			operationWithPriority = ElementOfPriority(listOfOperations.indexOf('^'), listOfOperations.indexOf('*'), listOfOperations.indexOf('/'), listOfOperations.indexOf('+'), listOfOperations.indexOf('-'), '^', '*', '/', '+', '-');
			if(operationWithPriority != ' ')
			{
				indexOfOperation = listOfOperations.indexOf(operationWithPriority);
				listOfValues.set(indexOfOperation, ExecuteOperation(listOfValues.get(indexOfOperation), listOfValues.get(indexOfOperation + 1), listOfOperations.get(indexOfOperation)));
				listOfValues.remove(indexOfOperation + 1);
				listOfOperations.remove(indexOfOperation);
			}
			else
				break;
		}
	}
	private static char ElementOfPriority(int index1, int index2, int index3, int index4, int index5, char elem1, char elem2, char elem3, char elem4, char elem5)
	{
		if(index1 != -1)
			return elem1;
		if((index2 < index3) && (index2 != -1))
			return elem2;
		if((index2 > index3) && (index3 != -1))
			return elem3;
		if((index2 < index3) && (index2 == -1))
			return elem3;
		if((index2 > index3) && (index3 == -1))
			return elem2;
		if((index4 < index5) && (index4 != -1))
			return elem4;
		if((index4 > index5) && (index5 != -1))
			return elem5;
		if((index4 < index5) && (index4 == -1))
			return elem5;
		if((index4 > index5) && (index5 == -1))
			return elem4;
		System.out.println("End reached");
		return ' ';
	}
	private static double ExecuteOperation(double v1, double v2, char op)
	{
		if(op == '^')
			return Math.pow(v1, v2);
		if(op == '*')
			return v1 * v2;
		if(op == '/')
			return v1 / v2;
		if(op == '+')
			return v1 + v2;
		if(op == '-')
			return v1 - v2;
		return 0.0;
	}
}
