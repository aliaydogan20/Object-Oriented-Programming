
// Bu ifade _mainTesterda da olmalıydı.
@SuppressWarnings("unchecked")
public interface Bigram <T> {

    public void readFile(String filename) throws Exception;
    public int numGrams();
    public int numOfGrams(T t1,T t2);
    public String toString();
}
