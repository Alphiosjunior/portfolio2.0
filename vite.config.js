import { defineConfig } from 'vite';

export default defineConfig({
  build: {
    lib: {
      entry: 'src/rum.js',
      name: 'rum',
      fileName: 'rum',
      formats: ['iife'],
    },
    outDir: 'dist',
    emptyOutDir: true,
  },
});
