public class NumberValidator {

    public static int validatePositiveNumber(int number) {
        if (number == 0) {
            throw new IllegalArgumentException("The number is zero — invalid input.");
        } else if (number < 0) {
            throw new IllegalArgumentException("The number is negative — invalid input.");
        }

        System.out.println("The number passed validation.");
        return number;
    }

    public static void main(String[] args) {
        try {
            System.out.println(validatePositiveNumber(0));
        } catch (Exception e) {
            System.out.println("Validation error: " + e.getMessage());
        }
    }
}
