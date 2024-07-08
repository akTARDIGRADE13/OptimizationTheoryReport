/* eslint-disable react/react-in-jsx-scope */
import { FC } from 'react';
import BaseVisualizer from 'components/BaseVisualizer/BaseVisualizer';
import Layout from 'components/Layout/Layout';
import Container from 'components/Container/Container';

const Home: FC = () => {
  return (
    <Layout>
      <Container>
        <BaseVisualizer>
          <h1>Home</h1>{' '}
        </BaseVisualizer>
      </Container>
    </Layout>
  );
};

export default Home;
