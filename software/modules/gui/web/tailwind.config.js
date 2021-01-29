module.exports = {
  purge: ["./src/**/*.{js,jsx,ts,tsx}", "./public/index.html"],
  darkMode: false, // or 'media' or 'class'
  theme: {
    extend: {
      colors: {
        gray: {
          DEFAULT: "#778FAC",
          50: "#F7F9FA",
          100: "#E9EDF2",
          200: "#CDD5E0",
          300: "#B0BECF",
          400: "#94A6BD",
          500: "#778FAC",
          600: "#5B7595",
          700: "#485C75",
          800: "#344356",
          900: "#212A36",
        },
      },
      boxShadow: { DEFAULT: "0px 0px 3px 0px rgba(0,0,0,0.3)" },
    },
  },
  variants: {
    extend: {},
  },
  plugins: [],
};
