import java.io.BufferedReader;
import java.io.FileReader;

@SuppressWarnings("unchecked")
public class BigramDyn<T> implements Bigram {

    private int dataType;
    private String[] bigramDynliste;
    public BigramDyn(int dataType) {
        this.dataType = dataType;
    }

    @Override
    public void readFile(String filename) throws Exception {

        FileReader fileReader;
        try {
            fileReader = new FileReader(filename);
        } catch (Exception ex) {
            throw new Exception("Dosya acilirken bir sorun olustu");
        }

        BufferedReader br = new BufferedReader(fileReader);
        try {
            String line;
            while ((line = br.readLine()) != null) {
                writeFromFileToList(line);
            }

            br.close();
        } catch (Exception ex) {
            throw new Exception("Dosya okurken bir sorun olustu \nHata :" + ex.getMessage());
        }
    }
    @Override
    public int numGrams() {
        return bigramDynliste.length - 1;
    }

    @Override
    public int numOfGrams(Object t1, Object t2) {
        int num = 0;// dizide kac tane t1 ve t2 bigramindan varmis ona bakiyoruz
        for (int i = 0; bigramDynliste.length - 1 > i; ++i) {
            if (t1.toString().equals(bigramDynliste[i]) && t2.toString().equals(bigramDynliste[i + 1]))
                ++num;
        }
        return num;
    }

    @Override
    public String toString() {
        int number = 0;
        String [] key = new String[bigramDynliste.length];
        int [] value = new int[bigramDynliste.length];

        for (int i = 0; bigramDynliste.length - 1 > i; ++i) {
            String temp = "" +  bigramDynliste[i] + "," + bigramDynliste[i + 1];
            int j;
            for(j= 0 ; number > j; ++j){
                // daha once kaydettigimiz string oldugu icin value sunu 1 artiriyoruz
                if(key[j].equals(temp)){
                    ++value[j];
                    break;
                }
            }
            // j number a esitse yeni bir string gelmistir bizde o yuzde diziye ekliyoruz ve value sunu 1 yapiyoruz
            if(j == number){
                key[j] = temp;
                value[j]= 1;
                ++number;
            }
        }
        // bigram lari en coktan en aza dogru siraliyoruz
        for(int i = 1 ; number > i ; ++i){
            for (int j = 0; number - i > j; ++j){
                if(value[j] < value[j+1])
                {
                    int temp = value[j];
                    value [j] = value [j+1];
                    value [j+1] = temp;
                    String tempString = key[j];
                    key[j] = key[j+1];
                    key[j+1] = tempString;
                }
           }
        }
        String result ="";
        for(int i = 0 ; number > i ; ++i){
            result+= key[i]+"\n";
        }
        return result;
    }

    private void writeFromFileToList(String line) throws Exception {
        String[] temp = line.split(" ");
        bigramDynliste = new String [temp.length];
        for (int i = 0; temp.length > i; ++i) {
            try {
                switch (dataType) {
                    case 1://integer sayisi dosyasinda geliyorsa ve integer degilse exception yiyecektir.
                        Integer.parseInt(temp[i]);
                        break;
                    case 3://double sayisi dosyasinda geliyorsa ve double degilse exception yiyecektir.
                        Double.parseDouble(temp[i]);
                        break;

                    default:
                        break;
                }//her bir stringi diziye atiyoruz
                bigramDynliste[i] = temp[i];
            } catch (Exception ex) {
                throw new Exception("Dosyada '" + temp[i] + "' stringine rastlandi");
            }
        }
    }
}
