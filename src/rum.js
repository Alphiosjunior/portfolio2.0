import { AwsRum } from 'aws-rum-web';

try {
  new AwsRum('614331ad-3712-4960-8edd-48280adc43b6', '1.0.0', 'eu-north-1', {
    sessionSampleRate: 1,
    identityPoolId: 'eu-north-1:7ab3b592-6b11-4dea-8881-359700f93aae',
    endpoint: 'https://dataplane.rum.eu-north-1.amazonaws.com',
    telemetries: ['performance', 'errors', 'http'],
    allowCookies: true,
    enableXRay: false,
  });
} catch (e) {}
