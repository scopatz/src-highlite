public interface TestIface : Object
{
	[CCode (cname = "test_preproc")]
	public virtual test_method ()
	{
		stdout.printf ("""multiline \literal string""");
	}
}

public abstract class TestClass : Object, TestIface
{
	#if 0
	public signal void test_signal (size_t size);
	#endif
}