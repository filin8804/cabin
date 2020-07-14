package object;

/**
 * Status: Pass
 */
public class ObjectTest {
	public static int staticVar;
	public int instanceVar;
	
	public static void main(String[] args) {
		int x = 32768; // ldc
		ObjectTest obj = new ObjectTest(); // new
		ObjectTest.staticVar = x; // putstatic
		x = ObjectTest.staticVar; // getstatic
		obj.instanceVar = x; // putfield
		x = obj.instanceVar; // getfield
		Object tmp = obj;
		if (tmp instanceof ObjectTest) { // instanceof
			obj = (ObjectTest) tmp; // checkcast
			System.out.println(obj.instanceVar == 32768 ? "Pass":"Fail");
			System.out.println(staticVar == 32768 ? "Pass":"Fail");
		} else {
			System.out.println("Fail");
		}
	}
}
