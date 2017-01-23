import java.io.BufferedReader;
import java.io.FileReader;
import java.util.*;

@SuppressWarnings("unchecked")
public class BigramMap<T> implements Bigram {

    private int dataType;
    private ArrayList bigramList = new ArrayList();
    private HashMap<String, Integer> hashMap;

    public BigramMap(int dataType) {
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
    public int numGrams() {// listenin sayisni bir eksigi bigram oluyor
        return bigramList.size() - 1;
    }

    @Override
    public int numOfGrams(Object t1, Object t2) {
        int num = 0;// dizide kac tane t1 ve t2 bigramindan varmis ona bakiyoruz
        for (int i = 0; bigramList.size() - 1 > i; ++i) {
            if (t1.toString().equals(bigramList.get(i)) && t2.toString().equals(bigramList.get(i + 1)))
                ++num;
        }
        return num;
    }

    @Override
    public String toString() {
        hashMap = new HashMap<String, Integer>();
        for (int i = 0; bigramList.size() - 1 > i; ++i) {
            String temp = "" + bigramList.get(i) + "," + bigramList.get(i + 1);
            if (hashMap.get(temp)==null)
                hashMap.put(temp, 1);
            else {
                int num = hashMap.get(temp);
                ++num;
                hashMap.put(temp, num);
            }
        }
        // bigram lari en cokdan en az a dogru siraliyoruz
        Map <String,Integer> sortedMap = sorting(hashMap);

        StringBuilder stringBuilder = new StringBuilder();
        for ( String key : sortedMap.keySet() ) {
            stringBuilder.append(key +"\n");
        }

        return stringBuilder.toString();
    }

    private void writeFromFileToList(String line) throws Exception {
        String[] temp = line.split(" ");

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
                }//her bir stringi listeye atiyoruz
                bigramList.add( temp[i]);
            } catch (Exception ex) {
                throw new Exception("Dosyada '" + temp[i] + "' stringine rastlandi");
            }
        }
    }

    public static <K, V extends Comparable<V>> Map<K, V>
    sorting(final Map<K, V> map) {
        Comparator<K> valueComp =
                new Comparator<K>() {
                    public int compare(K k1, K k2) {
                        int compare =
                                map.get(k2).compareTo(map.get(k1));
                        if (compare == 0)
                            return 1;
                        else
                            return compare;
                    }
                };

        Map<K, V> sorted =
                new TreeMap<K, V>(valueComp);
        sorted.putAll(map);
        return sorted;
    }

}
