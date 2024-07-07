import { defineConfig, loadEnv } from 'vite';
import react from '@vitejs/plugin-react';
import tsconfigPaths from 'vite-tsconfig-paths';

const cherryPickedKeys = [
  'SOME_KEY_IN_YOUR_ENV_FILE',
  'SOME_OTHER_KEY_IN_YOUR_ENV_FILE',
];

export default defineConfig(({ mode }) => {
  const env = loadEnv(mode, process.cwd(), '');
  const processEnv: { [key: string]: string } = {};
  cherryPickedKeys.forEach((key) => (processEnv[key] = env[key]));

  return {
    define: {
      'process.env': processEnv,
    },
    plugins: [react(), tsconfigPaths()],
    base: '/OptimizationTheoryReport/',
    resolve: {
      alias: {
        '/src/main.tsx': '/src/OptimizationTheoryReport/main.tsx',
      },
    },
    server: {
      watch: {
        usePolling: true,
      },
    },
  };
});
