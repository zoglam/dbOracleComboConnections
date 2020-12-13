import java.math.BigDecimal;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class ClientTest {

    public static void execute(Statement st){

    }

    public static void main(String[] args) throws SQLException {
        long sum = 0;


        for(int i = 0; i < 20; i++){
            final long startTime = System.nanoTime();
            try (Connection connection = DBUtil.getDataSource().getConnection();
                    Statement st = connection.createStatement();) {
                        
                String SQL = "SELECT * FROM customers";
                ResultSet rs = st.executeQuery(SQL);
                while (rs.next()) {
                    String _1 = rs.getString("CUSTOMERID");
                    String _2 = rs.getString("COMPANYNAME");
                    String _3 = rs.getString("CONTACTNAME");
                    String _4 = rs.getString("CONTACTTITLE");
                    String _5 = rs.getString("ADDRESS");
                    String _6 = rs.getString("CITY");
                    String _7 = rs.getString("REGION");
                    String _8 = rs.getString("POSTALCODE");
                    String _9 = rs.getString("COUNTRY");
                    String _10 = rs.getString("PHONE");
                    String _11 = rs.getString("FAX");

                    //System.out.println(_1 + '\t'+ _2 + '\t'+ _3 + '\t'+ _4);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            final long endTime = System.nanoTime();
            sum += endTime - startTime;
            System.out.println("Total execution time: " + ((endTime - startTime)/Math.pow(10,-6)));
        }
        System.out.println("Avg: "+(sum/20));
        sum = 0;
        for(int i = 0; i < 20; i++){
            final long startTime = System.nanoTime();
            try (Connection connection = DBUtilWithout.getDataSource().getConnection();
                    Statement st = connection.createStatement();) {
                        
                String SQL = "SELECT * FROM customers";
                ResultSet rs = st.executeQuery(SQL);
                while (rs.next()) {
                    String _1 = rs.getString("CUSTOMERID");
                    String _2 = rs.getString("COMPANYNAME");
                    String _3 = rs.getString("CONTACTNAME");
                    String _4 = rs.getString("CONTACTTITLE");
                    String _5 = rs.getString("ADDRESS");
                    String _6 = rs.getString("CITY");
                    String _7 = rs.getString("REGION");
                    String _8 = rs.getString("POSTALCODE");
                    String _9 = rs.getString("COUNTRY");
                    String _10 = rs.getString("PHONE");
                    String _11 = rs.getString("FAX");

                    //System.out.println(_1 + '\t'+ _2 + '\t'+ _3 + '\t'+ _4);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            final long endTime = System.nanoTime();
            sum += endTime - startTime;
            System.out.println("Total execution time: " + ((endTime - startTime)/Math.pow(10,-6)));
        }
        System.out.println("Avg: "+(sum/20));
    }
}
