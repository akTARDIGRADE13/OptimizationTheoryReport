/* eslint-disable react/react-in-jsx-scope */
import { FC } from 'react';
import { Routes, Route } from 'react-router-dom';
import { Helmet } from 'react-helmet';
import Home from 'routes/Home/Home';
import NotFound from 'routes/NotFound/NotFound';
import { VisualizerInfoProvider } from 'components/BaseVisualizer/context/VisualizerInfoProvider';
import './App.css';

const App: FC = () => {
  return (
    <>
      <Helmet>
        <title>Visualizer</title>
        <meta name="description" content="Visualizer" />
        <meta property="og:title" content="Visualizer" />
        <meta property="og:description" content="Visualizer" />
        <meta
          property="og:image"
          content="https://aktardigrade13.github.io/OptimizationTheoryReport/banner-meta.jpg"
        />
        <meta property="og:image:width" content="1200" />
        <meta property="og:image:height" content="670" />
        <meta property="og:image:type" content="image/jpg" />
        <meta property="og:image:alt" content="バナー" />
        <meta name="twitter:card" content="summary_large_image" />
        <meta name="twitter:site" content="@akTARDIGRADE13"></meta>
        <meta
          property="og:url"
          content="https://aktardigrade13.github.io/OptimizationTheoryReport/"
        />
        <meta property="og:type" content="website" />
        <meta property="og:locale" content="ja_JP" />
      </Helmet>
      <Routes>
        <Route
          path="/OptimizationTheoryReport/"
          element={
            <VisualizerInfoProvider>
              <Home />
            </VisualizerInfoProvider>
          }
        />
        <Route path="*" element={<NotFound />} />
      </Routes>
    </>
  );
};

export default App;
